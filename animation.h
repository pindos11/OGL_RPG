class anim{
	protected:
		int posx;
		int posy;
		float stepx;
		float stepy;
		int finished;
		int sizex;
		int sizey;
		int steps;
		int step;
		int sw_anim_next;
		int sw_anim_cur;
		int curtex;
		int stuck;
		
		GLuint atextures[5]; //5 tiles per any animation - GLuint texture IDs needed
	public:
		void setanim(int px, int py, int sx, int sy){
			posx=px;
			posy=py;
			sizex = sx;
			sizey = sy;
			finished = 1;
			stuck = 0;
		}
		
		virtual void set(GLuint texes[5],int isteps, float istepx, float istepy, int sw_anim){
			for(int i=0;i<5;i++){
				atextures[i]=texes[i];
			}
			
			steps = isteps;	//steps before finished
			step = 0;	//current step;
			
			stepx=istepx;	//speed x
			stepy=istepy;	//speed y
			
			sw_anim_next = sw_anim;	//amount of steps before changing tile
			sw_anim_cur = 0;	//steps with current tile done
			
			curtex = 0;		//current tile number from given 5
			finished = 0;
			//stuck = 0;
		}
		
		virtual GLuint doStep(){
			if(step>steps){	//sets finished to 1, returns 0 instead of GLuint texture ID
				finished=1;
				stuck = 0;
				return(atextures[curtex]);
			}
			step+=1;
			sw_anim_cur += 1;			
			if(sw_anim_cur>=sw_anim_next){	//changes tile each sw_anim_next steps
				sw_anim_cur=0;
				curtex+=1;
				if(curtex>=5){	//cycled playing animation
					curtex = 0;
				}
			}
			posx+=stepx;	//sets new pos for tile
			posy+=stepy;
			int aposx = posx/FIELD_TILE_SIZE;
			int aposy = posy/FIELD_TILE_SIZE;
			if(curf.can_walk(aposx,aposy+1)==0){
				posx-=stepx;
				posy-=stepy;
				finished=1;
				stuck = 1;
			}
			return(atextures[curtex]);
		}
		
		int getsx(){
			return sizex;
		}
		
		int getsy(){
			return sizey;
		}
		
		int getx(){
			return posx;
		}
		
		int gety(){
			return posy;
		}
		int fin(){
			return finished;
		}
		int get_stuck(){
			return stuck;
		}
		void unstuck(){
			stuck = 0;
		}
		float getstx(){
			return stepx;
		}
		float getsty(){
			return stepy;
		}	
};
