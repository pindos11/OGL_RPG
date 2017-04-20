int randint(int a, int b){
	if(a>b){
		return -1;
	}
	if(a==b){
		return -1;
	}
	int diff = b-a+1;
	int out = a+rand()%diff;
	return out;
}

std::vector<GLuint> textures;

float sox;
float soy;

GLuint shader_programme;
GLuint ppos_for_s;
struct game_cond{
	int paused;
	int mode; //slideshow or game itself
	
	game_cond(){
		paused = 0;
		mode = 1;  //1 - game 0 - slide
	}
};
game_cond game_i;

void slide_draw(int);

int curslide();

void add_hero(int,int,int);
void ask_hero();
void ask_hero_attack();

void add_mob(int,int,int);
void ask_mob();
void ask_mob_attack();

void init_hq();

void check_dead();
void mouse_func(int,int,int,int);
void offscreen(int,int);
void c_offscreen(int, int);

void draw_gui();

void rand_attacks();

void draw_field();
void add_field(int,int);

int mousex = 0;
int mousey = 0;

long int stime;
int ticks;
int loaded_tex;
int char_tex_start;
GLuint font;
std::string directions[9]={"s","n","e","w","nw","ne","sw","se","idle"};
struct cons_text{
	std::string text;
	int toWrite;
}added[5];

//Wave a[10]; //sound lol

int curfpx;
int curfpy;


void to_translate(int back){
	if(!back){
		glTranslatef(-sox,-soy,0);
	}
	else{
		glTranslatef(sox,soy,0);
	}
}

void add_text(std::string text){
	int emp = 4;
	for(int i=4;i>=0;i--){
		if(added[i].toWrite==0){
			emp = i;
		}
	}
	if(emp==4){
		for(int i=1;i<5;i++){
			added[i-1].text=added[i].text;
			added[i-1].toWrite=added[i].toWrite;
		}
		added[4].text=text;
		added[4].toWrite = 1;
	}
	else{
		added[emp].text=text;
		added[emp].toWrite = 1;
	}
}

void draw_polygon(int px, int py, int sx, int sy, GLuint texture, int transparent){
	if(transparent==1){
		glEnable(GL_BLEND);
	}
	else{
		glDisable(GL_BLEND);
	}
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_POLYGON) ;             
	  //glColor4f ( 1, 1, 1, 1);      
	  glTexCoord2d(0,1); glVertex2f(px-sx/2,py-sy/2);        
	  glTexCoord2d(1,1); glVertex2f(px+sx/2,py-sy/2);      
	  glTexCoord2d(1,0); glVertex2f(px+sx/2,py+sy/2);       
	  glTexCoord2d(0,0); glVertex2f(px-sx/2,py+sy/2);        
	glEnd();
}

void draw_text(){
	int size = 2;
	int x=10;
	int y=10;
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,font);
	for(int t=0;t<5;t++){
		if(added[t].toWrite==0){
			continue;
		}
		std::string inp = added[t].text;
		y=10+t*8*size;
		for(int i = 0;i<inp.length();i++){
			int out = inp.data()[i];
			if(out>64&&out<=90){
				out+=32;
			}
			if(out>96&&out<123){
				out-=97;
				int hgt = 0;
				int wdh = out%9;
				if(out>8){
					hgt = 1;
				}
				if(out>17){
					hgt = 2;
				}
				long double tsx,tsy,tex,tey;
				if(wdh == 0){
					tsx = 0.0;
				}
				else{
					tsx = wdh/9.0;
				}
				if(hgt == 0){
					tey = 1.0;
				}
				else{
					tey = (8.0-hgt)/8.0;
				}
				tex = (wdh+1.0)/9.0;
				tsy = (7.0-hgt)/8.0;
				//std::cout<<std::fixed<<tsx<<"/"<<tsy<<"/"<<tex<<"/"<<tey<<"\n";
				glBegin(GL_POLYGON);
					glTexCoord2d(tsx,tey); glVertex2f(5*size*i,y);  
					glTexCoord2d(tex,tey); glVertex2f(5*size*i+5*size,y); 
					glTexCoord2d(tex,tsy); glVertex2f(5*size*i+5*size,y+8*size); 
					glTexCoord2d(tsx,tsy); glVertex2f(5*i*size,y+8*size);   
				glEnd();    
					   
				//std::cout<<inp.data()[i]<<": "<<hgt<<"/"<<wdh<<"\n";
			}
			if(out>48&&out<58){
				out-=49;
				int hgt = 7;
				int wdh = out%9;
				long double tsx,tsy,tex,tey;
				if(wdh == 0){
					tsx = 0.0;
				}
				else{
					tsx = wdh/9.0;
				}
				if(hgt == 0){
					tey = 1.0;
				}
				else{
					tey = (8.0-hgt)/8.0;
				}
				tex = (wdh+1.0)/9.0;
				tsy = (7.0-hgt)/8.0;
				//std::cout<<std::fixed<<tsx<<"/"<<tsy<<"/"<<tex<<"/"<<tey<<"\n";
				glBegin(GL_POLYGON);
					glTexCoord2d(tsx,tey); glVertex2f(5*size*i,y);  
					glTexCoord2d(tex,tey); glVertex2f(5*size*i+5*size,y); 
					glTexCoord2d(tex,tsy); glVertex2f(5*size*i+5*size,y+8*size); 
					glTexCoord2d(tsx,tsy); glVertex2f(5*i*size,y+8*size);   
				glEnd();    		   
				//std::cout<<inp.data()[i]<<": "<<hgt<<"/"<<wdh<<"\n";
			}
			if(out==48){
				int hgt = 6;
				int wdh = 8;
				long double tsx,tsy,tex,tey;
				if(wdh == 0){
					tsx = 0.0;
				}
				else{
					tsx = wdh/9.0;
				}
				if(hgt == 0){
					tey = 1.0;
				}
				else{
					tey = (8.0-hgt)/8.0;
				}
				tex = (wdh+1.0)/9.0;
				tsy = (7.0-hgt)/8.0;
				//std::cout<<std::fixed<<tsx<<"/"<<tsy<<"/"<<tex<<"/"<<tey<<"\n";
				glBegin(GL_POLYGON);
					glTexCoord2d(tsx,tey); glVertex2f(5*size*i,y);  
					glTexCoord2d(tex,tey); glVertex2f(5*size*i+5*size,y); 
					glTexCoord2d(tex,tsy); glVertex2f(5*size*i+5*size,y+8*size); 
					glTexCoord2d(tsx,tsy); glVertex2f(5*i*size,y+8*size);   
				glEnd();    		   
			}
			//std::cout<<inp.data()[i]<<": "<<out<<"\n";
			//97-122 48-57
			
		}
	}
	
	
}

void resize(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow( 1024, 768);
}

void draw_shadows(){
	glUseProgram(shader_programme);
	glUniform2f(ppos_for_s,randint(509,515),randint(381,384));
	draw_polygon(1024/2,768/2,1024,768,textures[2],1);
	glUseProgram(0);
}

void display()
{                                 
	glClear(GL_COLOR_BUFFER_BIT);    
	glMatrixMode(GL_MODELVIEW);      
	glLoadIdentity();  
	if(game_i.mode==1){
		glPushMatrix();
		to_translate(0);
		draw_field(); 
		if(game_i.paused==0){
			ask_hero();
			ask_hero_attack();          
			ask_mob();
			ask_mob_attack();
			//to_translate(1);
			glPopMatrix();
			draw_shadows();
			draw_text();
		}
		else{
			glPopMatrix();
		}
		draw_gui();
	}
	else{
		slide_draw(77);
	}
	glutSwapBuffers(); 
}

void idle_draw(){
	if(game_i.mode==1){
		if(game_i.paused==0){
			struct timeval tp;
			gettimeofday(&tp, NULL);
			long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
			ms = abs(ms);
			//std::cout<<ms<<std::endl;
			//std::cout<<ms<<std::endl;
			if(abs(ms-stime)>70){
				for(int i=0;i<5;i++){
					if(added[i].toWrite){
						added[i].toWrite+=1;
						if(added[i].toWrite>50){
							for(int j=i;j<4;j++){
								added[j]=added[j+1];
							}
							added[4].toWrite=0;
						}
					}
				}
				ticks+=1;
				if(ticks>100){
					ticks = 1;
				}
				stime=ms;
				check_dead();
				rand_attacks();
				display();
			}
		}
	}
}

void load_tex_pack(const char * folder,int type){
	int to_load;
	if(type == 1){
		to_load = 45;
	}
	for(int i = loaded_tex;i<to_load+loaded_tex;i++){
		char name[100]="";
		//strcat(name,char(i));
		int div = ((i-loaded_tex)/5);
		strcat(name,folder);
		strcat(name,directions[div].data());
		char istr[2]="";
		itoa((i-loaded_tex)%5+1,istr,10);
		strcat(name,std::string(istr).data());
		strcat(name,".bmp");
		//std::cout<<"\n\n"<<name<<"\n\n";
		textures.push_back(LoadTexture(name));	
	}
	//std::cout<<"kek";
	loaded_tex+=to_load;
	
}

void load_single_tex(const char* tex){
	textures.push_back(LoadTexture(tex));
	loaded_tex+=1;
}

void load_textures(){
	font = LoadTexture("font/font4.bmp");
	loaded_tex = 0;
	//grass first;
	load_single_tex("images/grass.bmp");
	load_single_tex("images/grass-stone.bmp");
	load_single_tex("images/blank.bmp");
	load_single_tex("images/health.bmp");
	load_single_tex("images/health_out.bmp");
	load_single_tex("images/sand.bmp");//5
	load_single_tex("images/water.bmp");//6
	char_tex_start = loaded_tex-1;
	load_tex_pack("hero2/werebear/",1);
	load_tex_pack("hero2/werebear/attacks/",1);
	load_tex_pack("hero2/werebear/attacks/",1);
	load_tex_pack("hero2/skele1/",1);
	load_tex_pack("hero2/skele1/attacks/",1);
	load_tex_pack("hero2/skele1/attacks/",1);
	std::cout<<"loaded";

}

//void load_sounds(){
//	a[0].lWave("C:/WINDOWS/Media/ding.wav");
//}

void InitGL(int resx, int resy)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	ms = abs(ms);
	stime = ms;
	glutInitWindowSize( resx, resy );     
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("OGL_RPG_DEMO"); 
	glutDisplayFunc(display); 
	glutIdleFunc(idle_draw);
	glutMouseFunc(mouse_func);
	glutPassiveMotionFunc(offscreen);
	glutReshapeFunc(resize);
	glClearColor(0.7, 0.7, 0.7, 0.0); /* gray background */
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glDepthMask(GL_FALSE);
	glMatrixMode(GL_PROJECTION);      
	glLoadIdentity();                 
	gluOrtho2D( 0, resx, resy, 0);
	glMatrixMode(GL_MODELVIEW);
	load_textures();
	//load_sounds();
	init_hq();
	add_field(0,0);
	add_hero(1,resx/2,resy/2);
//	add_mob(2,200,200);
//	add_mob(2,300,200);
//	add_mob(2,200,300);
//	add_mob(2,100,200);
//	std::cout<<std::endl<<glGetString(GL_VERSION)<<std::endl<<glGetString(GL_SHADING_LANGUAGE_VERSION);	
	glewExperimental=TRUE;
  	GLenum err=glewInit();
  	if(err!=GLEW_OK) {
    	// Problem: glewInit failed, something is seriously wrong.
    	std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
    	exit(1);
  	}
  	const char* fragment_shader = read_shader_file("shaders/frag.txt");
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLint isCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
	
		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);
	
		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		std::cout<<std::endl;
		std::cout<<"Error compiling shader";
		std::cout<<std::endl;
		std::cout<<errorLog.data();
		glDeleteShader(fs); // Don't leak the shader.
		system("PAUSE");
		return;
	}
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glLinkProgram(shader_programme);
	ppos_for_s = glGetUniformLocation(shader_programme,"ppos");
	//glUseProgram(shader_programme);
	glutMainLoop(); 
}


