/*
 *  PolySceneLabel.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySceneLabel.h"

using namespace Polycode;

SceneLabel::SceneLabel(string fontName, wstring text, int size, float scale, int amode) : SceneEntity() {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode);
	this->scale = scale;
	setText(text);
	texture = NULL;
	mesh = new Mesh(Mesh::QUAD_MESH);
	mesh->createPlane(1,1);
}

SceneLabel::~SceneLabel() {
}

Label *SceneLabel::getLabel() {
	return label;
}

bool SceneLabel::testMouseCollision(float x, float y) {
	
	Matrix4 fullMatrix = getConcatenatedMatrix();
	if(billboardMode) {
		fullMatrix.m[0][0] = 1.0f * getScale().x;
		fullMatrix.m[0][1] = 0;
		fullMatrix.m[0][2] = 0;
		
		fullMatrix.m[1][0] = 0;
		fullMatrix.m[1][1] = 1.0f * getScale().y;
		fullMatrix.m[1][2] = 0;
		
		fullMatrix.m[2][0] = 0;
		fullMatrix.m[2][1] = 0;
		fullMatrix.m[2][2] = 1.0f * getScale().z;
	}
	
	Matrix4 camInverse = CoreServices::getInstance()->getRenderer()->getCameraMatrix().inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;	
	
	fullMatrix = fullMatrix * cmv;
	
	if(billboardMode && billboardRoll) {
		Quaternion q;
		q.createFromAxisAngle(0.0f, 0.0f, 1.0f, getRoll());
		Matrix4 tm = q.createMatrix();
		fullMatrix = tm * fullMatrix ;
	}		
	
	return false; //CoreServices::getInstance()->getRenderer()->test2DCoordinate(x, y, imagePolygon, fullMatrix, billboardRoll);
}

void SceneLabel::setText(wstring newText) {
	if(texture)
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
		
	label->setText(newText);	
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label);

	// TODO: resize it here
	
	bBoxRadius = label->getWidth()*scale;
}

void SceneLabel::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	renderer->setTexture(texture);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::NORMAL_DATA_ARRAY);		
	renderer->drawArrays(mesh->getMeshType());	
}
