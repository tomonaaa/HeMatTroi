#ifndef MODEL_H
#define MODEL_H

#include <glut.h>
#include <stdio.h>

#define MAX_VERTICES 10000
#define MAX_LINES 10000
#define PI 3.14159265358979323846
//#define PI 3.14
typedef struct Point3 {
	double x, y, z;
}Point3;
typedef Point3 Vector3;
typedef struct Model {
	int nVertices; // s? l??ng ??nh
	Point3 vertices[MAX_VERTICES]; // danh sách các ??nh
	int nEdges; // s? l??ng c?nh
	int edges[MAX_LINES][2]; // danh sách các c?nh
}Model;
void drawModelLines(Model* m);
void regularPolygon(Model* m, double r, int n);

Point3 point3(double x, double y, double z);
void drawModelLines(Model* m, Vector3 v);
void regularPolygon(Model* m, int n, double A0x, double A0y);
void regularPolygon1(Model* m, double r, int n, double startAngle);


#endif // !MODEL_H
#pragma once
