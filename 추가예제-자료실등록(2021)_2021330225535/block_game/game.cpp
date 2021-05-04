#include <glut.h>



int x = 1; // 블럭에 부딫칠 시 각도 변환 변수 ( 아래에서 위 로 칠시 "1" / 위에서 아래로 칠시 "0" )

int point = 0; // 아직 미구축 , 점수 구현 변수
int start = 1; //시작 변수
int life = 1; // 생명 변수		
float xx=0; // 막대 움직임 좌표 
float px=0.0, py = -0.785; // 공에 좌표 
float dx=0.001, dy=0.001; // 공에 각도 좌표 (진행방향) 	
int x_size = 0, y_size = 0; // 임시 변수 (단지 for문을 위한 변수) - 블럭 배열에서 임시 블럭 배열로 담는 역할을 함 
float block_x = 0.0, block_x_ = 0.0, block_y_ = 0.0, block_y = 0.0; // 임시 박스 좌표 변수	


float block[18][4] = {
					{-0.9, -0.75, 0.8, 0.9}, 
					{-0.7, -0.55, 0.8, 0.9}, 
					{-0.5, -0.35, 0.8, 0.9},
					{-0.3, -0.15, 0.8, 0.9}, 
					{-0.1, 0.05, 0.8, 0.9}, 
					{0.1, 0.25, 0.8 , 0.9}, 
					{0.3, 0.45, 0.8, 0.9}, 
					{0.5, 0.65, 0.8, 0.9}, 
					{0.7, 0.85, 0.8, 0.9},
					{-0.9, -0.75, 0.65, 0.75}, 
					{-0.7, -0.55, 0.65, 0.75}, 
					{-0.5, -0.35, 0.65, 0.75},
					{-0.3, -0.15, 0.65, 0.75}, 
					{-0.1, 0.05, 0.65, 0.75}, 
					{0.1, 0.25, 0.65 , 0.75}, 
					{0.3, 0.45, 0.65, 0.75}, 
					{0.5, 0.65, 0.65, 0.75}, 
					{0.7, 0.85, 0.65, 0.75}}; // 블럭 좌표 (x , x, y, y ) 순서

float temp_block[18][4]; // 블럭을 깰 때를 처리할 임시 블럭 배열 변수

void MyTimer(int value); // 타이머 선언 
void MyDisplay( ); // 그리기 선언
void MyKeyboard(char key, int x, int y); // 키보드 이벤트 선언  

void MyDisplay( )  // 그리기 
{  

    glClear(GL_COLOR_BUFFER_BIT); // 다시 그리기 (호출시)	 
	glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_POLYGON);        				
          glVertex3f(-0.1+xx, -0.9, 0.0); 
          glVertex3f(0.1+xx, -0.9, 0.0);  
 		  glVertex3f(0.1+xx, -0.8, 0.0);      
          glVertex3f(-0.1+xx, -0.8, 0.0);     
    glEnd( ); // 막대 그림 
	
	// temp box 
    for(x_size = 0; x_size < 18 ; x_size++)
	{
		
		if(start == 1)
		{
		for(y_size = 0; y_size < 4; y_size++)
		{
			temp_block[x_size][y_size] = block[x_size][y_size]; // 블럭을 깰시 처리하기 위해 임시 블럭 배열에 담음 
		}
		}
			block_x = temp_block[x_size][0];
		    block_x_ = temp_block[x_size][1];
		    block_y = temp_block[x_size][2];
		    block_y_ = temp_block[x_size][3];

			glColor3f(3.5, 5.2, 2.1);
			glBegin(GL_POLYGON);
			glVertex3f(block_x, block_y, 0);
			glVertex3f(block_x_, block_y, 0);
			glVertex3f(block_x_, block_y_, 0);
			glVertex3f(block_x, block_y_, 0);
			glEnd();
		
		
	} // 블럭 그리기	
		
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_POLYGON);        				
          glVertex3f(-0.02+px, -0.02+py, 0.0); 
          glVertex3f(0.02+px, -0.02+py, 0.0);  
 		  glVertex3f(0.02+px, 0.02+py, 0.0);      
          glVertex3f(-0.02+px, 0.02+py, 0.0);     
    glEnd( ); // 공 그리기
    glFlush( ); 
	
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) // 키보드 이벤트  
{ 
    switch (key){
		case 'a':
			
			xx = xx - 0.1; // a 를 눌를시 좌측으로 막대 이동 
			if ( start == 1)  // start 가 될 시 공에 좌표는 영향을 안받는다.
			{
			px = px - 0.1; // a 를 눌를시 좌측으로 공 이동 
			}
			if(xx < -0.9) // over 되는것을 막기 위한 조건 
			{
				if(start == 1)  // start 가 될 시 공에 좌표는 영향을 안받는다.
				{
			   px = -0.9; 
				}
               xx = -0.9;
			}
			glutPostRedisplay(); 
			break; 

		case 'd':

			xx = xx + 0.1; // d 를 눌를시 좌측으로 막대 이동 
			if(start == 1)  // start 가 될 시 공에 좌표는 영향을 안받는다.
			{
			px = px + 0.1; // d 를 눌를시 좌측으로 공 이동 
			}
			if(xx > 0.9) // over 되는 것을 막기 위한 조건
			{  
				if(start == 1) // start 가 될 시 공에 좌표는 영향을 안받는다.
				{
				px = 0.9;
				}
				xx = 0.9;
			}
			glutPostRedisplay(); 
			break;

		case 'p': // 재시작 모든 값을 초기화 한다. ( 블럭 다시 생성 및 공위치 막대위치 초기화) 
			if(life != 1) 
			{
			px = xx; 
			py = -0.795;
			dx = 0.001;
			dy = 0.001;
			life = 1;
			start = 1;
			x= 1;
			glutPostRedisplay(); 
			}
			break;
		case 's': // gane start 키 ( x 좌표 0을 기준으로 0보다 크면 우측방향으로 0보다 작거나 같으면 좌픅방향으로 나가게 설정)
			 if(start != 0)
			 {
			 if(xx > 0) 
			 {
               dx = 0.001; 
			   glutTimerFunc(1 ,MyTimer, 1);
			 }
			 else
			 {
				 dx = -0.001;
				 glutTimerFunc(1 ,MyTimer, 1);
			 }
			 }
			 start = 0;	 // 시작 시 변수 0 으로 변경함으로 시작됬음을 알림. ( 방향키를 눌러도 공에 방향은 변하지 않도록 하기위함)
			 break;

	}
}


void MyTimer(int value)
{
	px = px + dx; // 공에 x 좌표
	py = py + dy;  // 공에 y 좌표

	if (px > 1) { // x 좌표가 우측 끝에 닿을 시 좌측방향으로 진행
		px = 1.0;
	    dx = -0.001; 

	}if (py > 1) { // y 좌표가 위에 닿을 시 아래방향으로 진행
		py = 1.0;
		dy = -0.001; 
		x = 0; // x = 0으로 함으로써 위에서 내려가는 것을 표현 (공이 블럭을 맞출 때의 각도 조정하기 위함)
	}
	if (px < -1) {  // x 좌표가 좌측 끝에 닿을 시 우측방향으로 진행
		px = -1.0;
		dx = 0.001;
	}

	if(py >= 0.65) // 공에 y 좌표가 블럭위치 위에 갈 시 조건.
	{
		for(x_size = 17; x_size >= 0 ; x_size--) // 블럭에 좌표값과 비교하기 위한 반복문
		{
			if(py >= temp_block[x_size][2] && py <= temp_block[x_size][3]) // 블럭과의 y 값 따짐
			{
				if((px <= temp_block[x_size][0] && px >= temp_block[x_size][1]) || (px >= temp_block[x_size][0] && px <= temp_block[x_size][1])) // 블럭과의 x 값 따짐 
				{ 
					temp_block[x_size][0] = 0.0; // 블럭에 좌표값 안에 공이 들어갈 시 블럭 없애기
					temp_block[x_size][1] = 0.0; // 블럭에 좌표값 안에 공이 들어갈 시 블럭 없애기
					temp_block[x_size][2] = 0.0; // 블럭에 좌표값 안에 공이 들어갈 시 블럭 없애기
					temp_block[x_size][3] = 0.0; // 블럭에 좌표값 안에 공이 들어갈 시 블럭 없애기 
					if(x == 1) // 공에 방향에 따른 각도 계산 ( 아래에서 쳤을 시 아래로 방향 변경)
					{
					   dy = -0.001;
					}
					else // 공에 방향에 따른 각도 계산 ( 위에서 쳤을 시 위로 방향 변경 )
						dy = 0.001;
					break;
				}
			}
		}
    }
	if (py < -0.8) { // 공이 바닥에 닿을 시... 
		if (px < xx - 0.15 || px > xx + 0.15) { 
                life = 0; 
		}
	else {
		 if(px >= xx) // 공이 막대에 맞을시 좌표값 수정 ( 막대에 중간에서 우측끝에 걸칠 시 우측방향 진행 )
			 {
			   x = 1; // 아래에서 위로 올라가고 있음을 알림
               dx = 0.001;
			   dy = 0.001;
			 }
			 else // 공이 막대에 맞을시 좌표값 수정 ( 막대에 좌측끝에서 중간 사이에 걸칠 시 좌측방향 진행 )
			 {
				 x = 1; // 아래에서 위로 올라가고 있음을 알림
				 dx = -0.001;
				 dy = 0.001;
			 }
		}
	}

    glutPostRedisplay( );
	if(life == 1)
	{
		glutTimerFunc(1, MyTimer, 1); // 죽지 않았다면 timer 계속 콜백
	}

}

int main(int argc, char **argv )
{
	glutInit(&argc, argv);             //  윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);

    glutCreateWindow("OpenGL Drawing Example"); 
	
	glClearColor(0.4, 0.4, 0.4, 0.0);  //  상태 변수 설정
	glPointSize(8.0); 
	glLineWidth(5);
	glColor3f(0.0, 1.0, 0.0);  

   	glutDisplayFunc(MyDisplay);        //  콜백함수 등록
	glutKeyboardFunc(MyKeyboard);

	glClear(GL_COLOR_BUFFER_BIT); 

    glutMainLoop( );	                //  이벤트루프 진입				
    return 0; 
}
