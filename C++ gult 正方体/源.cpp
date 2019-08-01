#include <stdio.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
using namespace std;

//Բ���ʺ�
#define GL_PI 3.1415f
//��ȡ��Ļ�Ŀ��
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//���ó���Ĵ��ڴ�С
GLint windowWidth = 400;
GLint windowHeight = 300;
//��x����ת�Ƕ�
GLfloat xRotAngle = 0.0f;
//��y����ת�Ƕ�
GLfloat yRotAngle = 0.0f;
//��֧�ֵĵ��С��Χ
GLfloat sizes[2];
//��֧�ֵĵ��С����
GLfloat step;
//����ͶӰ�����ջ���
GLint iMaxProjectionStackDepth;
//����ģ����ͼ�����ջ���
GLint iMaxModeviewStackDepth;
//������������ջ���
GLint iMaxTextureStackDepth;

GLint iCoordinateaxis = 2;//�Ƿ���ʾ������
GLint iProjectionMode = 1;//ͶӰģʽ
void changSize(GLint w, GLint h);

//�˵��ص�����
void processMenu(int value){
	switch (value){
	case 1:
		iCoordinateaxis = 1;
		break;
	case 2:
		iCoordinateaxis = 2;
		break;
	case 3:
		iProjectionMode = 1;
		//ǿ�Ƶ��ô��ڴ�С�仯�ص�����������ͶӰģʽΪ����ͶӰ
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case 4:
		iProjectionMode = 2;
		//ǿ�Ƶ��ô��ڴ�С�仯�ص�����������ͶӰģʽΪ͸��ͶӰ
		changSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	default:
		break;
	}
	//���»���
	glutPostRedisplay();
}

//��ʾ�ص�����
void renderScreen(void){
	//��������ɫ����Ϊ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//��������������Ϊ��ǰ������ɫ����ɫ�������Ȼ�������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//����ǰMatrix״̬��ջ
	glPushMatrix();

	//����ϵ��x����תxRotAngle
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//����ϵ��y����תyRotAngle
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//����ƽ������
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
	if(2==iProjectionMode){
	glTranslatef(0.0f,0.0f,-200.0f);
	}*/
	if (1 == iCoordinateaxis){
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(-90.0f, 00.0f, 0.0f);
		glVertex3f(90.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -90.0f, 0.0f);
		glVertex3f(0.0f, 90.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -90.0f);
		glVertex3f(0.0f, 0.0f, 90.0f);
		glEnd();

		glPushMatrix();
		glTranslatef(90.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 90.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 90.0f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(3, 6, 10, 10);
		glPopMatrix();
	}

	// Draw six quads
	glFrontFace(GL_CW);
	glBegin(GL_QUADS);
	// Front Face
	// White
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Yellow
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(50.0f, 0.0f, 50.0f);

	// Red
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Magenta
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Top Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	// Right face
	// White
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glEnd();

	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
	// Bottom Face
	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Left face
	// Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 50.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 50.0f);

	// Back Face
	// Cyan
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 0.0f);

	// Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);

	// Black
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glEnd();

	//�ָ�ѹ��ջ��Matrix
	glPopMatrix();
	//����������������ָ��
	glutSwapBuffers();
}

//����Redering State 
void setupRederingState(void){
	glEnable(GL_DEPTH_TEST);	//ʹ����Ȳ���
	//glFrontFace(GL_CCW);		//�������ʱ�뷽��Ϊ����
	glEnable(GL_CULL_FACE);		//����ʾ����
	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//���������ʹ�������
	glPolygonMode(GL_FRONT, GL_FILL);//���������ʹ�������
	glPolygonMode(GL_BACK, GL_LINE);//���������ʹ�������
	glShadeModel(GL_SMOOTH);


	//����������ɫΪ��ɫ
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//���û滭��ɫΪ��ɫ
	glColor3f(1.0f, 1.0f, 0.0f);
	//ʹ����Ȳ���
	glEnable(GL_DEPTH_TEST);
	//��ȡ��֧�ֵĵ��С��Χ
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//��ȡ��֧�ֵĵ��С����
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	//��ȡ����ͶӰ�����ջ���
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &iMaxProjectionStackDepth);
	//��ȡ����ģ����ͼ�����ջ���
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &iMaxModeviewStackDepth);
	//��ȡ������������ջ���
	glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &iMaxTextureStackDepth);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
	printf("iMaxProjectionStackDepth=%d\n", iMaxProjectionStackDepth);
	printf("iMaxModeviewStackDepth=%d\n", iMaxModeviewStackDepth);
	printf("iMaxTextureStackDepth=%d\n", iMaxTextureStackDepth);
}

//���ڴ�С�仯�ص�����
void changSize(GLint w, GLint h){
	//������
	GLfloat ratio;
	//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)
	GLfloat coordinatesize = 100.0f;
	//���ڿ��Ϊ��ֱ�ӷ���
	if ((w == 0) || (h == 0))
		return;
	//�����ӿںʹ��ڴ�Сһ��
	glViewport(0, 0, w, h);
	//��ͶӰ����Ӧ�����ľ������
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰָ���ľ���Ϊ��λ����
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
	//����ͶӰ
	if (1 == iProjectionMode){
		printf("glOrtho\n");
		if (w<h)
			glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
		else
			glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
		//��ǰ��������Ϊģ����ͼ����
		glMatrixMode(GL_MODELVIEW);
		//���õ�ǰָ���ľ���Ϊ��λ����
		glLoadIdentity();
	}
	else{
		printf("gluPerspective\n");
		gluPerspective(60, ratio, 10.0f, 500.0f);
		//��ǰ��������Ϊģ����ͼ����
		glMatrixMode(GL_MODELVIEW);
		//���õ�ǰָ���ľ���Ϊ��λ����
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -200.0f);
	}
}

//�������봦��ص�����
void specialKey(int key, int x, int y){

	if (key == GLUT_KEY_UP){
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN){
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT){
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT){
		yRotAngle += 5.0f;
	}
	//���»���
	glutPostRedisplay();
}

void timerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}

int main(int argc, char* argv[])
{
	//�˵�
	GLint iMainMenu;
	GLint iCoordinateaxisMenu;
	GLint iOrthoOrPerspectMenu;
	//��ʼ��glut 
	glutInit(&argc, argv);
	//ʹ��˫����������Ȼ�������
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//��ȡϵͳ�Ŀ�����
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//��ȡϵͳ�ĸ�����
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������
	glutCreateWindow("�����ĵ�һ��������");
	//���ô��ڴ�С
	glutReshapeWindow(windowWidth, windowHeight);
	//���ھ�����ʾ
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//���ڴ�С�仯ʱ�Ĵ�����
	glutReshapeFunc(changSize);
	//������ʾ�ص����� 
	glutDisplayFunc(renderScreen);
	//���ð������봦��ص�����
	glutSpecialFunc(specialKey);
	//�˵��ص�����
	iCoordinateaxisMenu = glutCreateMenu(processMenu);
	//��Ӳ˵�
	glutAddMenuEntry("Display coordinate axis", 1);
	glutAddMenuEntry("Don't dispaly coordinate axis", 2);
	iOrthoOrPerspectMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("Ortho", 3);
	glutAddMenuEntry("Perspect", 4);
	iMainMenu = glutCreateMenu(processMenu);
	glutAddSubMenu("Whether Display coordinate axis", iCoordinateaxisMenu);
	glutAddSubMenu("Ortho Or Perspect", iOrthoOrPerspectMenu);
	//���˵��񶨵�����Ҽ���
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(10, timerFunc, 1);
	//����ȫ����Ⱦ����
	setupRederingState();
	glutMainLoop();

	return 0;
}