#define SCROLLSPEED 10
void mouse_func(int btn,int state,int mx, int my){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		//std::cout<<std::endl<<"x: "<<mx<<" y: "<<my;
		heroes[0].set_moving(mx,my);
	}
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		//std::cout<<std::endl<<"x: "<<mx<<" y: "<<my;
		heroes[0].set_attack(mx,my,2);
	}
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN){
		//a[0].play();
		if(game_i.paused==0){
			game_i.paused = 1;
		}
		else{
			game_i.paused = 0;
		}
//		//std::cout<<std::endl<<"x: "<<mx<<" y: "<<my;
//		add_mob(2,mx,my);
//		char ix[3]="";char iy[3]="";
//		itoa(mx,ix,10);
//		itoa(my,iy,10);
//		//added=std::string("1234567890");
//		add_text(std::string("MOB: x")+std::string(ix)+std::string(" y")+std::string(iy));
	}
}

void offscreen(int mx, int my){
	//omx = mx;
	//omy = my;
}

void c_offscreen(int mx, int my){
//	if(mx<3){
//		sox-=SCROLLSPEED;
//	}
//	if(mx>793){
//		sox+=SCROLLSPEED;
//	}
//	if(my<3){
//		soy-=SCROLLSPEED;
//	}
//	if(my>593){
//		soy+=SCROLLSPEED;
//	}
}
