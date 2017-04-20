void draw_health(float left,int px, int py, int sx, int sy, GLuint texture){
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_POLYGON) ;             
	  //glColor4f ( 1, 1, 1, 1);      
	  glTexCoord2d(0,1.0*left); glVertex2f(px,py+sy*(1.0-left));        
	  glTexCoord2d(1,1.0*left); glVertex2f(px+sx,py+sy*(1.0-left));      
	  glTexCoord2d(1,0); glVertex2f(px+sx,py+sy);       
	  glTexCoord2d(0,0); glVertex2f(px,py+sy);        
	glEnd();
}

void draw_gui(){
	//3 - hp
	//4 - hp outline
	int hp = heroes[0].get_health();
	float left = float(hp)/100;
	draw_health(left,30,768-110,100,100,textures[3]);
	draw_health(1.0,30,768-110,100,100,textures[4]);
	
	//arrows
}
