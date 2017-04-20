class monster : public hero{
	public:
		anim* ask_move(){
			if(health<=0){
				unset();
			}
			posx = heroanim.getx();
			posy = heroanim.gety();
			int targx = heroes[0].getx()-sox;
			int targy = heroes[0].gety()-soy;
			
			int tpx = targx-posx+sox;
			int tpy = targy-posy+soy;
			if(ticks%5==0){
				if(heroanim.get_stuck()>0){
					int mov = randint(10,20);
					if(randint(0,1)){
						mov*=-1;
					}
					targx = posx+mov;
					mov = randint(10,20);
					if(randint(0,1)){
						mov*=-1;
					}
					targy = posy+mov;
					set_moving(targx-sox,targy-soy);
				}
				else{
					float dist = sqrt(tpx*tpx+tpy*tpy);
					if(dist<40){
						set_attack(targx,targy,2);
					}
					if(dist>40){
						set_moving(targx,targy);
					}
				}
			}
			if(heroanim.fin()){
				heroanim.set(idle,5,0,0,1);
			}
			return &heroanim;
		}
};
monster mobs[20];

