void check_dead(){
	if(heroes[0].get_health()<=0){
		add_text(std::string(""));
		add_text(std::string("UR DEAD"));
		add_text(std::string("RESTARTING"));
		int old_px = heroes[0].getx();
		int old_py = heroes[0].gety();
		int new_px = randint(10,900);
		int new_py = randint(10,900);
		std::cout<<"\n"<<"x:"<<sox<<"/"<<old_px<<"y:"<<soy<<"/"<<old_py<<"\n";
		sox -= old_px-new_px;
		soy -= old_py-new_py;
		init_hq();
		init_mobs();
		add_hero(1,new_px,new_py);
	}
}

void rand_attacks(){
	for(int i=0;i<20;i++){
		if(mobs[i].isset()==1){
			//std::cout<<"1";
			return;
		}
	}
	int mobsnum = randint(2,7);
	for(int i = 0;i<mobsnum;i++){
		int range = randint(150,250);
		if(randint(0,1)){
			range*=-1;
		}
		int px = range+heroes[0].getx();
		range = randint(150,250);
		if(randint(0,1)){
			range*=-1;
		}
		int py = range+heroes[0].gety();
		if(px>770){
			px = 770;
		}
		if(px<0){
			px = 20;
		}
		if(py>570){
			py = 570;
		}
		if(py<0){
			py = 20;
		}
		if(curf.can_walk(px/FIELD_TILE_SIZE,py/FIELD_TILE_SIZE+1)){
			add_mob(2,px,py);
		}		
	}
}
