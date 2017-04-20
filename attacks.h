class hit : public anim{
	protected:
		int pierce_obstacles;
		int damage;
		int checked;
		int sett;
	public:
		void set(GLuint texes[5],int isteps, int istepx, int istepy, int dmg){
			if(sett){
				return;
			}
			for(int i=0;i<5;i++){
				atextures[i]=texes[i];
			}
			
			steps = isteps;	//steps before finished
			step = 0;	//current step;
			
			stepx=istepx;	//speed x
			stepy=istepy;	//speed y
			
			sw_anim_next = 1;	//amount of steps before changing tile
			sw_anim_cur = 0;	//steps with current tile done
			
			curtex = 0;		//current tile number from given 5
			finished = 0;
			
			damage = dmg;
			checked = 0;
			sett = 1;
			//stuck = 0;
		}
		
		GLuint doStep(){
			if(step>steps){	//sets finished to 1
				//std::cout<<1;
				finished=1;
				stuck = 0;
				sett = 0;
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
			if(curf.can_walk(aposx,aposy)==0 && pierce_obstacles==0){
				posx-=stepx;
				posy-=stepy;
				finished=1;
				stuck = 1;
				checked = 1;
			}
			return(atextures[curtex]);
		}
		
		int isset(){
			return sett;
		}
		
		int get_damage(){
			return damage;
		}
		
		int is_check(){
			return checked;
		}
		
		int check(){
			checked = 1;
		}
		
};
