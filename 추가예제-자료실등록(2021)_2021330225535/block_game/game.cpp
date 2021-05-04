#include <glut.h>



int x = 1; // ���� �΋Hĥ �� ���� ��ȯ ���� ( �Ʒ����� �� �� ĥ�� "1" / ������ �Ʒ��� ĥ�� "0" )

int point = 0; // ���� �̱��� , ���� ���� ����
int start = 1; //���� ����
int life = 1; // ���� ����		
float xx=0; // ���� ������ ��ǥ 
float px=0.0, py = -0.785; // ���� ��ǥ 
float dx=0.001, dy=0.001; // ���� ���� ��ǥ (�������) 	
int x_size = 0, y_size = 0; // �ӽ� ���� (���� for���� ���� ����) - �� �迭���� �ӽ� �� �迭�� ��� ������ �� 
float block_x = 0.0, block_x_ = 0.0, block_y_ = 0.0, block_y = 0.0; // �ӽ� �ڽ� ��ǥ ����	


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
					{0.7, 0.85, 0.65, 0.75}}; // �� ��ǥ (x , x, y, y ) ����

float temp_block[18][4]; // ���� �� ���� ó���� �ӽ� �� �迭 ����

void MyTimer(int value); // Ÿ�̸� ���� 
void MyDisplay( ); // �׸��� ����
void MyKeyboard(char key, int x, int y); // Ű���� �̺�Ʈ ����  

void MyDisplay( )  // �׸��� 
{  

    glClear(GL_COLOR_BUFFER_BIT); // �ٽ� �׸��� (ȣ���)	 
	glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_POLYGON);        				
          glVertex3f(-0.1+xx, -0.9, 0.0); 
          glVertex3f(0.1+xx, -0.9, 0.0);  
 		  glVertex3f(0.1+xx, -0.8, 0.0);      
          glVertex3f(-0.1+xx, -0.8, 0.0);     
    glEnd( ); // ���� �׸� 
	
	// temp box 
    for(x_size = 0; x_size < 18 ; x_size++)
	{
		
		if(start == 1)
		{
		for(y_size = 0; y_size < 4; y_size++)
		{
			temp_block[x_size][y_size] = block[x_size][y_size]; // ���� ���� ó���ϱ� ���� �ӽ� �� �迭�� ���� 
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
		
		
	} // �� �׸���	
		
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_POLYGON);        				
          glVertex3f(-0.02+px, -0.02+py, 0.0); 
          glVertex3f(0.02+px, -0.02+py, 0.0);  
 		  glVertex3f(0.02+px, 0.02+py, 0.0);      
          glVertex3f(-0.02+px, 0.02+py, 0.0);     
    glEnd( ); // �� �׸���
    glFlush( ); 
	
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) // Ű���� �̺�Ʈ  
{ 
    switch (key){
		case 'a':
			
			xx = xx - 0.1; // a �� ������ �������� ���� �̵� 
			if ( start == 1)  // start �� �� �� ���� ��ǥ�� ������ �ȹ޴´�.
			{
			px = px - 0.1; // a �� ������ �������� �� �̵� 
			}
			if(xx < -0.9) // over �Ǵ°��� ���� ���� ���� 
			{
				if(start == 1)  // start �� �� �� ���� ��ǥ�� ������ �ȹ޴´�.
				{
			   px = -0.9; 
				}
               xx = -0.9;
			}
			glutPostRedisplay(); 
			break; 

		case 'd':

			xx = xx + 0.1; // d �� ������ �������� ���� �̵� 
			if(start == 1)  // start �� �� �� ���� ��ǥ�� ������ �ȹ޴´�.
			{
			px = px + 0.1; // d �� ������ �������� �� �̵� 
			}
			if(xx > 0.9) // over �Ǵ� ���� ���� ���� ����
			{  
				if(start == 1) // start �� �� �� ���� ��ǥ�� ������ �ȹ޴´�.
				{
				px = 0.9;
				}
				xx = 0.9;
			}
			glutPostRedisplay(); 
			break;

		case 'p': // ����� ��� ���� �ʱ�ȭ �Ѵ�. ( �� �ٽ� ���� �� ����ġ ������ġ �ʱ�ȭ) 
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
		case 's': // gane start Ű ( x ��ǥ 0�� �������� 0���� ũ�� ������������ 0���� �۰ų� ������ ���G�������� ������ ����)
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
			 start = 0;	 // ���� �� ���� 0 ���� ���������� ���ۉ����� �˸�. ( ����Ű�� ������ ���� ������ ������ �ʵ��� �ϱ�����)
			 break;

	}
}


void MyTimer(int value)
{
	px = px + dx; // ���� x ��ǥ
	py = py + dy;  // ���� y ��ǥ

	if (px > 1) { // x ��ǥ�� ���� ���� ���� �� ������������ ����
		px = 1.0;
	    dx = -0.001; 

	}if (py > 1) { // y ��ǥ�� ���� ���� �� �Ʒ��������� ����
		py = 1.0;
		dy = -0.001; 
		x = 0; // x = 0���� �����ν� ������ �������� ���� ǥ�� (���� ���� ���� ���� ���� �����ϱ� ����)
	}
	if (px < -1) {  // x ��ǥ�� ���� ���� ���� �� ������������ ����
		px = -1.0;
		dx = 0.001;
	}

	if(py >= 0.65) // ���� y ��ǥ�� ����ġ ���� �� �� ����.
	{
		for(x_size = 17; x_size >= 0 ; x_size--) // ���� ��ǥ���� ���ϱ� ���� �ݺ���
		{
			if(py >= temp_block[x_size][2] && py <= temp_block[x_size][3]) // ������ y �� ����
			{
				if((px <= temp_block[x_size][0] && px >= temp_block[x_size][1]) || (px >= temp_block[x_size][0] && px <= temp_block[x_size][1])) // ������ x �� ���� 
				{ 
					temp_block[x_size][0] = 0.0; // ���� ��ǥ�� �ȿ� ���� �� �� �� ���ֱ�
					temp_block[x_size][1] = 0.0; // ���� ��ǥ�� �ȿ� ���� �� �� �� ���ֱ�
					temp_block[x_size][2] = 0.0; // ���� ��ǥ�� �ȿ� ���� �� �� �� ���ֱ�
					temp_block[x_size][3] = 0.0; // ���� ��ǥ�� �ȿ� ���� �� �� �� ���ֱ� 
					if(x == 1) // ���� ���⿡ ���� ���� ��� ( �Ʒ����� ���� �� �Ʒ��� ���� ����)
					{
					   dy = -0.001;
					}
					else // ���� ���⿡ ���� ���� ��� ( ������ ���� �� ���� ���� ���� )
						dy = 0.001;
					break;
				}
			}
		}
    }
	if (py < -0.8) { // ���� �ٴڿ� ���� ��... 
		if (px < xx - 0.15 || px > xx + 0.15) { 
                life = 0; 
		}
	else {
		 if(px >= xx) // ���� ���뿡 ������ ��ǥ�� ���� ( ���뿡 �߰����� �������� ��ĥ �� �������� ���� )
			 {
			   x = 1; // �Ʒ����� ���� �ö󰡰� ������ �˸�
               dx = 0.001;
			   dy = 0.001;
			 }
			 else // ���� ���뿡 ������ ��ǥ�� ���� ( ���뿡 ���������� �߰� ���̿� ��ĥ �� �������� ���� )
			 {
				 x = 1; // �Ʒ����� ���� �ö󰡰� ������ �˸�
				 dx = -0.001;
				 dy = 0.001;
			 }
		}
	}

    glutPostRedisplay( );
	if(life == 1)
	{
		glutTimerFunc(1, MyTimer, 1); // ���� �ʾҴٸ� timer ��� �ݹ�
	}

}

int main(int argc, char **argv )
{
	glutInit(&argc, argv);             //  ������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);

    glutCreateWindow("OpenGL Drawing Example"); 
	
	glClearColor(0.4, 0.4, 0.4, 0.0);  //  ���� ���� ����
	glPointSize(8.0); 
	glLineWidth(5);
	glColor3f(0.0, 1.0, 0.0);  

   	glutDisplayFunc(MyDisplay);        //  �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyboard);

	glClear(GL_COLOR_BUFFER_BIT); 

    glutMainLoop( );	                //  �̺�Ʈ���� ����				
    return 0; 
}
