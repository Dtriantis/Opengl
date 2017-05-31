
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <GL/freeglut.h>

using namespace std;

#define N 64

GLint viewWidth = 600, viewHeight = 600;

void DrawSphere(int i, int j, int k);
void breakCubes();
bool break_cube_front = false;
bool break_all_cubes_front = false;
void makeACube();

bool print_flag = false;
bool light_flag = false;

void print_apothema();
int apothema=0;

bool mprosta = false;
bool pisw = true;
bool dexia = false;
bool aristera = false;

//game matrix
float game_matrix[N][N][N];
int game_score = 50;
int move_count=0;

//lights
void lightBulb();
void lightingFunc();
void RenderString(void *font, const char* string);
int light_step=0.0f;
float spotExponent = 2.0;
float PI = 3.14159265359;
bool lightbulb_flag=false;

// angle of rotation for the camera direction
float angle=0.0;

float deltaAngle = 0.0; // additional angle change when dragging
float deltaMove = 0.0; // initially camera doesn't move

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

float deltaAngley = 0.0; // additional angle change when dragging
float angley=0.0;

// Mouse drag control
int isDraggingy = 0; // true when dragging
int yDragStart = 0; // records the x-coordinate when dragging starts

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

//for camera control camera
float k=1.0f,ax=0.0f,ay=0.0f;
float y2=0.0f;
float Y3=0.0;	//change hight in y-axis

// XZ initial camera position
float x=32.4f,z=32.4f,y=2.0f;
float XXX=0.0f;

/**************************************************/
/*********************COLORS***********************/
/**************************************************/

const float colors[5][3] = {
     {0.0f,0.0f,1.0f},          //green
     {1.0f, 1.0f, 0.0f},			//yellow
     {1.0f,0.0f,0.0f},          //red
     {0.0f,1.0f,0.0f},          //blue
     {1.0f, 0.0f, 1.0f}			//magenta
};

/**************************************************/
/***************INIT GAME MATRIX*******************/
/**************************************************/

void initGameMatrix(){
	int i=0,k=0,j=0;
	
	for(i=0;i<64;i++){
			for(j=0;j<64;j++){
					for(k=0;k<64;k++){
						game_matrix[i][j][k]=-1;
				}
			}
	}
}

/**************************************************/
/************DRAW** GRID***************************/
/**************************************************/

void createGrid(){
	int i;

	glColor3f(1.0f, 1.0f, 1.0f);	
	for(i=0;i<=64;i++){
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f+i, 0.0f);	
			glVertex3f(64.0f, 0.0f+i, 0.0f);
		glEnd();
		glBegin(GL_LINES);					
			glVertex3f(0.0f+i, 64.0f, 0.0f);		
			glVertex3f(0.0f+i, 0.0f, 0.0f);
		glEnd();
	}
	for(i=0;i<=64;i++){
			glVertex3f(64.0f, 0.0f, 0.0f+i);		
			glVertex3f(0.0f,  0.0f, 0.0f+i);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0.0f+i,  0.0f, 0.0f);		
			glVertex3f(0.0f+i,  0.0f, 64.0f);
		glEnd();
	}
	for(i=0;i<=64;i++){
		glBegin(GL_LINES);
			glVertex3f(0.0f,  0.0f+i, 0.0f);		
			glVertex3f(0.0f,  0.0f+i, 64.0f);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0.0f,  64.0f, 0.0f+i);		
			glVertex3f(0.0f,  0.0f, 0.0f+i);
		glEnd();
	}
}

/**************************************************/
/**************DRAW THE CUBES**********************/
/**************************************************/

void DrawCube(int i, int j, int k, int color1)

{

    glColor3f(colors[color1][0],colors[color1][1],colors[color1][2]);
	glBegin(GL_QUADS);
		glNormal3d(0, 0, -1);					
		glVertex3f(0.0f+i, 0.0f+j, 0.0f+k);		
		glVertex3f(0.0f+i, 1.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 0.0f+k);
		glVertex3f(0.0f+i, 0.0f+j, 0.0f+k);		
	glEnd();
	glBegin(GL_QUADS);
		glNormal3d(0, 0, 1);				
		glVertex3f(0.0f+i, 0.0f+j, 1.0f+k);		
		glVertex3f(0.0f+i, 1.0f+j, 1.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 1.0f+k);
		glVertex3f(1.0f+i, 0.0f+j, 1.0f+k);			
	glEnd();
	glBegin(GL_QUADS);
		glNormal3d(-1, 0, 0);				
		glVertex3f(0.0f+i, 0.0f+j, 0.0f+k);		
		glVertex3f(0.0f+i, 1.0f+j, 0.0f+k);		
		glVertex3f(0.0f+i, 1.0f+j, 1.0f+k);
		glVertex3f(0.0f+i, 0.0f+j, 1.0f+k);		
	glEnd();
	glBegin(GL_QUADS);
		glNormal3d(1, 0, 0);					
		glVertex3f(1.0f+i, 0.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 1.0f+k);
		glVertex3f(1.0f+i, 0.0f+j, 1.0f+k);			
	glEnd();
	glBegin(GL_QUADS);
		glNormal3d(0, -1, 0);					
		glVertex3f(0.0f+i, 0.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 0.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 0.0f+j, 1.0f+k);
		glVertex3f(0.0f+i, 0.0f+j, 1.0f+k);		
	glEnd();
	glBegin(GL_QUADS);
		glNormal3d(0, 1, 0);					
		glVertex3f(0.0f+i, 1.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 0.0f+k);		
		glVertex3f(1.0f+i, 1.0f+j, 1.0f+k);
		glVertex3f(0.0f+i, 1.0f+j, 1.0f+k);	
	glEnd();
}

/**************************************************/
/************DRAW SPHERE***************************/
/**************************************************/

void DrawSphere(int i, int j, int k){
	
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.0);
	glTranslatef(i,j,k);
	glutSolidSphere(0.3, 50, 40);
	glPopMatrix();
	
}

/**************************************************/
/*********INIT FIRST FLOOR WITH RANDOM CUBES*******/
/**************************************************/

void drawFirstFloor(){
	int i=0;
	int j=0;
	
	for(i=0; i<64; i++){
		for(j=0; j<64; j++){
			game_matrix[i][0][j]=rand()%4;
		}
	}
}

/**************************************************/
/********DRAW EVERY CUBE IN EVERY FRAME************/
/**************************************************/

void renderMatrix(){
    int w=0,x=0,q=0;
    for(w=0;w<N;w++){
        for(x=0;x<N;x++){
            for(q=0;q<N;q++){
            //check if its red
               if(game_matrix[w][x][q]==0)
                           DrawCube(w,x,q,0);
            //check if its green
              if(game_matrix[w][x][q]==1)
                           DrawCube(w,x,q,1);
            //check if its blue
              if(game_matrix[w][x][q]==2)
                           DrawCube(w,x,q,2); 
              //check if its yellow
              if(game_matrix[w][x][q]==3)
                           DrawCube(w,x,q,3); 
              //magenta cube
              if(game_matrix[w][x][q]==4)
                        DrawCube(w,x,q,4);
              //draw light solid sphere
              if(game_matrix[w][x][q]==-2)
			DrawSphere(w,x,q);                          
              }
         }
    }              
}

	int current_x;
	int current_y;
	int current_z; 
	
void current_place_in_the_map(float xx,float yy,float zz){
	
	cout << current_x << " " << current_y << " " << current_z << endl;
	
}

/**************************************************/
/***********KEYBOARD KEYS**************************/
/**************************************************/

void processNormalKeys(unsigned char key, int x, int y) {


	//float fraction = 0.1f;

	switch (key) {
		
		case 119 :
			if((int)z==0 ){ break;
			}
			else {		
					z += lz;
					move_count++;
					light_step++;

		}break;
		case 115 :						//back
			if((int)z==63){break;
		}else{
					z -= lz;
					move_count++;
					light_step++;
			}break;
		case 100 :						//right
					if((int)XXX==63){break;
		}else{
					k++;
					move_count++;
					light_step++;
			}

			//	}			
			break;
		case 97 :						//left
					if((int)XXX==0){break;
		}else{
					k--;
					move_count++;
					light_step++;
		}
			//	}
			break;			
   		case 108 :		//case L place a light
					lightBulb();
					move_count=0;
					
			break;
			
		case 32 :	{	//case spacebar cube stock
					print_flag = true;
					if(game_matrix[current_x][current_y-2][current_z] != 4 && game_matrix[current_x][current_y-2][current_z] !=0 ){

						apothema=apothema+game_matrix[current_x][current_y-2][current_z];
						game_matrix[current_x][current_y-2][current_z]=0;}
			}break;	
					
		case 109 :		//m make cube in front of me
					makeACube();
			break;
			
		case 110 :		//n break front
					break_cube_front = true;
					breakCubes();
			break;
				
		case 98 :		//b break all front
					break_all_cubes_front = true;
					breakCubes();
			break;
		}

	if (key == 27)
		exit(0);
}

/**************************************************/
/***************MOUSE CONTROL**********************/
/**************************************************/

void update(void) 
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * lz * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}
void mouseMove(int x, int y) 
{ 	
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		lz = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
	
}

/**************************************************/
/***************COMPUTE ANGLE**********************/
/**************************************************/

void computeAngle(){
	
	float my_angle,polaplasio=6.0;
	
	my_angle=abs(angle);
	
	if(angle>6.0){
		my_angle = fmod(angle,polaplasio);}
		
		//angle 0.0 to 6.0

		if(my_angle>5.25 || my_angle<0.75){
			pisw=true;}
			else{pisw=false;}
		if(my_angle>0.75 && my_angle<2.25){
			aristera = true;}
			else {aristera=false;}
		if(my_angle>2.25 && my_angle<3.75){
			mprosta = true;}
			else{ mprosta=false;}
		if(my_angle>3.75 && my_angle<5.25){
			dexia = true;}
			else{ dexia=false;}
}

/**************************************************/
/***********MAKE A CUBE****************************/
/**************************************************/

void makeACube(){

	if(mprosta){	//turned less than 45 so make cube in front of me
		game_matrix[current_x][current_y-1][current_z-2]=rand()%4;
	}
		if(dexia){	//cube right
		game_matrix[current_x+2][current_y-1][current_z]=rand()%4;
	}
		if(aristera){	//cube left
		game_matrix[current_x-2][current_y-1][current_z]=rand()%4;
	}
		if(pisw){
		game_matrix[current_x][current_y-1][current_z+2]=rand()%4;
	}
	
	game_score=game_score+5;
	apothema--;
}


/**************************************************/
/***********MOVES RULES***************************/
/**************************************************/
int epipeda_flag = 0;

void playersPositionAndMoves(){

	if(game_matrix[current_x][current_y-1][current_z] ==0 ||	//if you are on cube elevate
	game_matrix[current_x][current_y-1][current_z] ==1 ||
	game_matrix[current_x][current_y-1][current_z] ==2 ||
	game_matrix[current_x][current_y-1][current_z] ==3){
		Y3++;
		epipeda_flag++;
	}
	
	if(game_matrix[current_x][current_y-2][current_z] ==-1){
		Y3--;
		epipeda_flag--;
	}
	
	if(y+Y3<0){ 	//fall nowhere go back to init posotion
		
		lx=0.0f;
		lz=-1.0f;
		k=1.0f;
		ax=0.0f;
		ay=0.0f;
		y2=0.0f;
		Y3=0.0;	
		x=32.4f;
		z=32.4f;
		y=2.0f;
		XXX=0.0f;
		
		epipeda_flag=epipeda_flag-4;
	
	}
	game_score=game_score+epipeda_flag*5;
	epipeda_flag=0;
	
	
}

/**************************************************/
/***********BREAK CUBES****************************/
/**************************************************/

void breakCubes(){
	
	int cube_x = (int)XXX;
	int cube_y = (int)y;
	int cube_z = (int)z;
	int allcubes=0;
	
	if(break_cube_front == true)
			{
		if(mprosta){
		game_matrix[cube_x][cube_y-1][cube_z-2]=-1;
	}
		if(dexia){
		game_matrix[cube_x+2][cube_y-1][cube_z]=-1;
	}
		if(aristera){
		game_matrix[cube_x-2][cube_y-1][cube_z]=-1;
	}
		if(pisw){
		game_matrix[cube_x][cube_y-1][cube_z+2]=-1;
	}
				
			}
	if(break_all_cubes_front==true)
			{
		if(mprosta){
			for(allcubes=0; allcubes<64; allcubes++){
				game_matrix[cube_x][allcubes][cube_z-2]=-1;
			}
		}
		if(dexia){
			for(allcubes=0; allcubes<64; allcubes++){
				game_matrix[cube_x+2][allcubes][cube_z]=-1;
			}
		}
		if(aristera){
			for(allcubes=0; allcubes<64; allcubes++){
				game_matrix[cube_x-2][allcubes][cube_z]=-1;
			}
		}
		if(pisw){
			for(allcubes=0; allcubes<64; allcubes++){
				game_matrix[cube_x][allcubes][cube_z+2]=-1;
				}
			}
		game_score=game_score-5;
		}
	break_cube_front = false;
	break_all_cubes_front = false;

}

/**************************************************/
/***********MOVES COUNTER**************************/
/**************************************************/

void moving_counter(){
		
	if(move_count >90 ){
		
		light_flag=true;
		
		}
}

/**************************************************/
/*****************FANARI***************************/
/**************************************************/

void lightBulb (){


	//where to place the light
		if(mprosta){
		game_matrix[current_x][current_y][current_z-1]=-2;
	}
		if(dexia){	
		game_matrix[current_x+1][current_y][current_z]=-2;
	}
		if(aristera){	
		game_matrix[current_x-1][current_y][current_z]=-2;
	}
		if(pisw){
		game_matrix[current_x][current_y][current_z+1]=-2;
	}
	lightbulb_flag=true;
	
	glLoadIdentity();

	glEnable(GL_LIGHT2);
	GLfloat light_diffuse2[] = { 1.0, 1.0, 1.0, 1.0  };

	GLfloat light_position2[] = {(float)current_x,(float)current_y+17.0f,(float)current_z, 1.0f };
	GLfloat spotDir2[] = { (float)current_x, (float)current_y, (float)current_z };

	glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,95);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotDir2);	
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
	
	}

/**************************************************/
/*********LIGHT FUNCTIONS**************************/
/**************************************************/

void lightingFunc(){


	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
    GLfloat diffuse[] = {1, 1, 0.6, 1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0+light_step, 65.0, 1.0+light_step, 0.0 };
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if(light_flag==true){
		
	glDisable(GL_LIGHT0);
		
	glEnable(GL_LIGHT1);
	GLfloat amb_light[] = {0.1, 0.1, 0.1, 1.0};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb_light);
		
				}
}

/**************************************************/
/*****************PRINTS***************************/
/**************************************************/

void print_apothema(){
	
	char text[100];
	char text2[100];
	glMatrixMode(GL_PROJECTION);
	
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 600, 0.0, 600);

	sprintf(text,"CUBE STOCK %d ",apothema);
	glColor3f(1.0f, 0.5f, 1.0f);
	
	sprintf(text2,"GAME SCORE %d ",game_score);
	glColor3f(1.0f, 0.5f, 1.0f);
	
	glRasterPos2i(10, 10);
	for(int i = 0; text[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	
	glRasterPos2i(10, 25);
	for(int i = 0; text2[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
	}
	
	print_flag = false;
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glFlush();
}

/**************************************************/
/*************RENDER*******************************/
/**************************************************/

void renderScene(void) {
	int i=0,j=0,k2=0;
	
	//Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reset transformations
	glLoadIdentity();

	//light functions
	lightingFunc();
	
	if(print_flag == true){
		print_apothema();
	}

	//central cube is magenta!!!
	game_matrix[32][0][32]=4;

	playersPositionAndMoves();
	moving_counter();
	
	XXX=x+k;
	
	current_x = (int)XXX;
	current_y = (int)y+Y3;
	current_z = (int)z;
	
	current_place_in_the_map(XXX,y,z);
	cout << game_matrix[(int)XXX][(int)y-2][(int)z] << endl;
	
	// Set the camera with buttons
	gluLookAt(	XXX, y+y2+Y3, z,
			XXX+lx, y+Y3,  z+lz,		
			0.0f, 1.0f,  0.0f);
		
	//set lightbulb for only 30 moves
	if(lightbulb_flag==true){
		if(move_count>30){
				glDisable(GL_LIGHT2);
			
			for(i=0;i<64;i++){
			for(j=0;j<64;j++){
					for(k2=0;k2<64;k2++){
						if(game_matrix[i][j][k2]==-2){
							game_matrix[i][j][k2]=-1;}
				}
			}
			
		}
	}	}

	computeAngle();
	
	//draw grid
	createGrid();
	
	//draw matrix
	renderMatrix();
	
	glutSwapBuffers();
}

/**************************************************/
/**********WINDOW FUNCTIONS************************/
/**************************************************/

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

/**************************************************/
/******************MAIN****************************/
/**************************************************/

int main (int argc, char **argv) {

	//init Glut and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(viewWidth, viewHeight);
	glutCreateWindow("mymine");

	//init all matrix values to -1
	initGameMatrix();
	
	//random for cubes on first floor
	srand(time(NULL));
	
	//init first floor
	drawFirstFloor();
	        
	//register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//Keyboard functions
	glutKeyboardFunc(processNormalKeys);
		
	glutIdleFunc(update); // incremental update for mouse move
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	
	glutMainLoop();

	return 1;
} 
