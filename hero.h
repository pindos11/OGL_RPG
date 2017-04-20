#include <math.h>
class hero{
	protected:
		int posx;
		int posy;
		int step;
		int type;
		int set;
		
		int health;
		int att_damage;
		
		GLuint south[5];		//tiles for each direction
		GLuint north[5];		//45*sizeof(int) to ease coding
		GLuint east[5];			//only 8 directions: idi nahui potomu 4to
		GLuint west[5];
		GLuint north_west[5];
		GLuint north_east[5];
		GLuint south_west[5];
		GLuint south_east[5];
		GLuint idle[5];
		GLuint southaa[5];		//tiles for each direction
		GLuint northaa[5];		//45*sizeof(int) to ease coding
		GLuint eastaa[5];			//only 8 directions: idi nahui potomu 4to
		GLuint westaa[5];
		GLuint north_westaa[5];
		GLuint north_eastaa[5];
		GLuint south_westaa[5];
		GLuint south_eastaa[5];
		
		GLuint southa[5];		//tiles for each direction
		GLuint northa[5];		//45*sizeof(int) to ease coding
		GLuint easta[5];			//only 8 directions: idi nahui potomu 4to
		GLuint westa[5];
		GLuint north_westa[5];
		GLuint north_easta[5];
		GLuint south_westa[5];
		GLuint south_easta[5];
		GLuint empty_attack[5];
		
		anim heroanim;
		hit heroattack;
	public:
		int isset(){
			return set;
		}
		void unset(){
			set = 0;
		}
		void seth(int px, int py, int htype, int  cam){
			for(int direction=1;direction<10;direction++){
				for(int i=0;i<5;i++){
					switch(direction){
						case(1):south[i]=0;break;
						case(2):north[i]=0;break;
						case(3):east[i]=0;break;
						case(4):west[i]=0;break;
						case(5):north_west[i]=0;break;
						case(6):north_east[i]=0;break;
						case(7):south_west[i]=0;break;
						case(8):south_east[i]=0;break;
						case(9):idle[i]=0;break;
					}	
				}
			}
			for(int i =0;i<5;i++){
				empty_attack[i]=textures[2];
			}
			set = 1;
			int sx,sy;
			if(htype==1){
				sx = 60;
				sy = 60;
			}
			if(htype==2){
				sx = 60;
				sy = 60;
			}
			heroanim.setanim(px,py,sx,sy);
			heroattack.setanim(px,py,sx,sy);
			posx = px;
			posy = py;
			if(htype==1){
				step = 6;
				health = 100;
			}
			else{
				step = 5;
				health = 5;
			}
			//std::cout<<step;
		}
		int load_tiles(int direction,GLuint tiles[5]){
			for(int i=0;i<5;i++){
				switch(direction){
					case(1):south[i]=tiles[i];break;
					case(2):north[i]=tiles[i];break;
					case(3):east[i]=tiles[i];break;
					case(4):west[i]=tiles[i];break;
					case(5):north_west[i]=tiles[i];break;
					case(6):north_east[i]=tiles[i];break;
					case(7):south_west[i]=tiles[i];break;
					case(8):south_east[i]=tiles[i];break;
					case(9):idle[i]=tiles[i];break;
					default:return(0);
				}	
			}
			heroanim.set(idle,5,0,0,2);
			return(1);
		}
		int load_attacks(int direction,GLuint tiles[5]){
			for(int i=0;i<5;i++){
				switch(direction){
					case(1):southaa[i]=tiles[i];break;
					case(2):northaa[i]=tiles[i];break;
					case(3):eastaa[i]=tiles[i];break;
					case(4):westaa[i]=tiles[i];break;
					case(5):north_westaa[i]=tiles[i];break;
					case(6):north_eastaa[i]=tiles[i];break;
					case(7):south_westaa[i]=tiles[i];break;
					case(8):south_eastaa[i]=tiles[i];break;
					default:return(0);
				}	
			}
			heroanim.set(idle,5,0,0,2);
			return(1);
		}
		int load_projectiles(int direction,GLuint tiles[5]){
			for(int i=0;i<5;i++){
				switch(direction){
					case(1):southa[i]=tiles[i];break;
					case(2):northa[i]=tiles[i];break;
					case(3):easta[i]=tiles[i];break;
					case(4):westa[i]=tiles[i];break;
					case(5):north_westa[i]=tiles[i];break;
					case(6):north_easta[i]=tiles[i];break;
					case(7):south_westa[i]=tiles[i];break;
					case(8):south_easta[i]=tiles[i];break;
					default:return(0);
				}	
			}
			heroanim.set(idle,5,0,0,2);
			return(1);
		}
		void set_moving(int px,int py){
			int tpx = px-posx+sox;
			int tpy = py-posy+soy;
			if(abs(tpx)<10&&abs(tpy)<10){
				return;
			}
			int dir = 0;
			if(tpx==0){
				if(tpy>0){
					dir = 2;
				}
				if(tpy<0){
					dir = 1;
				}
			}
			if(tpy==0){
				if(tpx>0){
					dir = 3;
				}
				if(tpx<0){
					dir = 4;
				}
			}
			if(tpx==0 && tpy==0){
				dir = 9;
			}
			if(tpx>0 && tpy<0){
				float tgmove = tpy/tpx;
				if(tgmove>-0.87f){
					dir = 3;
				}	
				if(tgmove<-0.87f&&tgmove>-1.73f){
					dir = 6;//
				}
				if(tgmove<-1.73f){
					dir = 2;
				}
			}
			if(tpx>0 && tpy>0){
				float tgmove = tpy/tpx;
				if(tgmove<0.87f){
					dir = 3;
				}	
				if(tgmove>0.87f&&tgmove<1.73f){
					dir = 8;
				}
				if(tgmove>1.73f){
					dir = 1;
				}
			}
			if(tpx<0 && tpy<0){
				float tgmove = tpy/tpx;
				if(tgmove<0.87f){
					dir = 4;
				}	
				if(tgmove>0.87f&&tgmove<1.73f){
					dir = 5;//
				}
				if(tgmove>1.73f){
					dir = 2;
				}
			}
			if(tpx<0 && tpy>0){
				float tgmove = tpy/tpx;
				if(tgmove>-0.87f){
					dir = 4;
				}	
				if(tgmove<-0.87f&&tgmove>-1.73f){
					dir = 7;
				}
				if(tgmove<-1.73f){
					dir = 1;
				}
			}
			float dist = sqrt(tpx*tpx+tpy*tpy);
			int steps = dist/step;
			float stepx = tpx/steps;
			float stepy = tpy/steps;
			//std::cout<<std::endl<<dir<<" "<<dist<<" "<<stepx<<"/"<<stepy<<" step: "<<step;
			switch(dir){
				case(1):heroanim.set(south,steps,stepx,stepy,2);break;
				case(2):heroanim.set(north,steps,stepx,stepy,2);break;
				case(3):heroanim.set(east,steps,stepx,stepy,2);break;
				case(4):heroanim.set(west,steps,stepx,stepy,2);break;
				case(5):heroanim.set(north_west,steps,stepx,stepy,2);break;
				case(6):heroanim.set(north_east,steps,stepx,stepy,2);break;
				case(7):heroanim.set(south_west,steps,stepx,stepy,2);break;
				case(8):heroanim.set(south_east,steps,stepx,stepy,2);break;
				case(9):heroanim.set(idle,5,0,0,1);break;	
		}
	}
	
	void set_attack(int px, int py, int atype){
			int tpx = px-posx+sox;
			int tpy = py-posy+soy;
			if(abs(tpx)<10&&abs(tpy)<10){
				return;
			}
			int dir = 0;
			if(tpx==0){
				if(tpy>0){
					dir = 2;
				}
				if(tpy<0){
					dir = 1;
				}
			}
			if(tpy==0){
				if(tpx>0){
					dir = 3;
				}
				if(tpx<0){
					dir = 4;
				}
			}
			if(tpx==0 && tpy==0){
				dir = 9;
			}
			if(tpx>0 && tpy<0){
				float tgmove = tpy/tpx;
				if(tgmove>-0.87f){
					dir = 3;
				}	
				if(tgmove<-0.87f&&tgmove>-1.73f){
					dir = 6;//
				}
				if(tgmove<-1.73f){
					dir = 2;
				}
			}
			if(tpx>0 && tpy>0){
				float tgmove = tpy/tpx;
				if(tgmove<0.87f){
					dir = 3;
				}	
				if(tgmove>0.87f&&tgmove<1.73f){
					dir = 8;
				}
				if(tgmove>1.73f){
					dir = 1;
				}
			}
			if(tpx<0 && tpy<0){
				float tgmove = tpy/tpx;
				if(tgmove<0.87f){
					dir = 4;
				}	
				if(tgmove>0.87f&&tgmove<1.73f){
					dir = 5;//
				}
				if(tgmove>1.73f){
					dir = 2;
				}
			}
			if(tpx<0 && tpy>0){
				float tgmove = tpy/tpx;
				if(tgmove>-0.87f){
					dir = 4;
				}	
				if(tgmove<-0.87f&&tgmove>-1.73f){
					dir = 7;
				}
				if(tgmove<-1.73f){
					dir = 1;
				}
			}
			float dist = sqrt(tpx*tpx+tpy*tpy);
			float ddist = 1;
			if(dist>30){
				ddist = 30/dist;
				dist = 30;
			}
			int steps = dist/5;
			float stepx = (tpx/steps)*ddist;
			float stepy = (tpy/steps)*ddist;
			//std::cout<<std::endl<<dir<<" "<<dist<<" "<<stepx<<"/"<<stepy<<" step: "<<step;
			if(atype!=2){
			switch(dir){
				case(1):heroattack.set(southa,steps,stepx,stepy,5);heroanim.set(southaa,5,0,0,1);break;
				case(2):heroattack.set(northa,steps,stepx,stepy,5);heroanim.set(northaa,5,0,0,1);break;
				case(3):heroattack.set(easta,steps,stepx,stepy,5);heroanim.set(eastaa,5,0,0,1);break;
				case(4):heroattack.set(westa,steps,stepx,stepy,5);heroanim.set(westaa,5,0,0,1);break;
				case(5):heroattack.set(north_westa,steps,stepx,stepy,5);heroanim.set(north_westaa,5,0,0,1);break;
				case(6):heroattack.set(north_easta,steps,stepx,stepy,5);heroanim.set(north_eastaa,5,0,0,1);break;
				case(7):heroattack.set(south_westa,steps,stepx,stepy,5);heroanim.set(south_westaa,5,0,0,1);break;
				case(8):heroattack.set(south_easta,steps,stepx,stepy,5);heroanim.set(south_eastaa,5,0,0,1);break;
				}
			}
			else{
			switch(dir){
				case(1):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(southaa,5,0,0,2);break;
				case(2):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(northaa,5,0,0,2);break;
				case(3):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(eastaa,5,0,0,2);break;
				case(4):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(westaa,5,0,0,2);break;
				case(5):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(north_westaa,5,0,0,2);break;
				case(6):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(north_eastaa,5,0,0,2);break;
				case(7):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(south_westaa,5,0,0,2);break;
				case(8):heroattack.set(empty_attack,steps,stepx,stepy,5);heroanim.set(south_eastaa,5,0,0,2);break;
				}	
			}
			
	}
	
	
	anim* ask_move(){
		posx = heroanim.getx();
		posy = heroanim.gety();
		if(heroanim.fin()){
			heroanim.set(idle,5,0,0,1);
		}
		return &heroanim;
	}
	
	hit* ask_attack(){
		return &heroattack;
	}
	
	int getx(){
		return posx;
	}
	int gety(){
		return posy;
	}
	void deal_damage(int dmg){
		health-=dmg;
	}
	int get_health(){
		return health;
	}
			
};
hero heroes[20];
