#pragma once
#ifndef PERLIN_H
#define PERLIN_H

double PerlinNoise(double x, double y, double z);
double fade(double t);//ƽ��
double lerp(double t, double a, double b);//��ֵ
double grad(int hash, double x, double y, double z);//�ݶ�
void prepare();
#endif // !PERLIN_H