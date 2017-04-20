void init_mobs(){
	for(int i = 0;i<20;i++){
		mobs[i].unset();
	}
}
void init_hq(){
	for(int i = 0;i<20;i++){
		heroes[i].unset();
	}
}

void add_hero(int type, int px, int py){
	for(int i=0;i<20;i++){
		if(heroes[i].isset()){
			continue;
		}
		int cam = 0;
		if(i==0){
			cam = 1;
		}
		heroes[i].seth(px,py,type,cam);
		int offset = (type-1)*135+char_tex_start;
		int offsetattack = offset+45;
		int offsetaa = offset+90;
		int ctr = 0;
		if(type==1 || type==2){
			for(int j=1;j<10;j++){
				GLuint tiles[5]={textures[offset+1+ctr],textures[offset+2+ctr],textures[offset+3+ctr],textures[offset+4+ctr],textures[offset+5+ctr]};
				GLuint tiles2[5]={textures[offsetattack+1+ctr],textures[offsetattack+2+ctr],textures[offsetattack+3+ctr],textures[offsetattack+4+ctr],textures[offsetattack+5+ctr]};
				GLuint tiles3[5]={textures[offsetaa+1+ctr],textures[offsetaa+2+ctr],textures[offsetaa+3+ctr],textures[offsetaa+4+ctr],textures[offsetaa+5+ctr]};
				ctr+=5;
				heroes[i].load_tiles(j,tiles);
				heroes[i].load_projectiles(j,tiles2);
				heroes[i].load_attacks(j,tiles3);
			}
		}
		break;
	}	
}

void add_mob(int type, int px, int py){
	for(int i=0;i<20;i++){
		if(mobs[i].isset()){
			continue;
		}
		mobs[i].seth(px,py,type,0);
		int offset = (type-1)*135+char_tex_start;
		int offsetattack = offset+45;
		int offsetaa = offset+90;
		int ctr = 0;
		if(type==1 || type==2){
			for(int j=1;j<10;j++){
				GLuint tiles[5]={textures[offset+1+ctr],textures[offset+2+ctr],textures[offset+3+ctr],textures[offset+4+ctr],textures[offset+5+ctr]};
				GLuint tiles2[5]={textures[offsetattack+1+ctr],textures[offsetattack+2+ctr],textures[offsetattack+3+ctr],textures[offsetattack+4+ctr],textures[offsetattack+5+ctr]};
				GLuint tiles3[5]={textures[offsetaa+1+ctr],textures[offsetaa+2+ctr],textures[offsetaa+3+ctr],textures[offsetaa+4+ctr],textures[offsetaa+5+ctr]};
				ctr+=5;
				mobs[i].load_tiles(j,tiles);
				mobs[i].load_projectiles(j,tiles2);
				mobs[i].load_attacks(j,tiles3);
			}
		}
		break;
	}	
}

void ask_mob(){
	for(int i=0;i<20;i++){
		if(mobs[i].isset()==0){
			continue;
		}
		anim* anm = mobs[i].ask_move();
		GLuint tile = anm->doStep();
		//std::cout<<" px: "<<anm->getx()<<" py: "<<anm->gety()<<" sx: "<<anm->getsx()<<" sy: "<<anm->getsy()<<": ";
		draw_polygon(anm->getx(),anm->gety(),anm->getsx(),anm->getsy(),tile,1);
	}
}

void ask_hero(){
	for(int i=0;i<20;i++){
		if(heroes[i].isset()==0){
			continue;
		}
		anim* anm = heroes[i].ask_move();
		GLuint tile = anm->doStep();
		if(i==0 && !anm->fin()){
			sox+=anm->getstx();
			soy+=anm->getsty();
		}
		//std::cout<<" px: "<<anm->getx()<<" py: "<<anm->gety()<<" sx: "<<anm->getsx()<<" sy: "<<anm->getsy()<<": ";
		draw_polygon(anm->getx(),anm->gety(),anm->getsx(),anm->getsy(),tile,1);
	}
}

void ask_hero_attack(){
	for(int i=0;i<20;i++){
		if(heroes[i].isset()==0){
			continue;
		}
		hit* anm = heroes[i].ask_attack();
		GLuint tile = anm->doStep();
		if(anm->is_check()==0 && anm->isset()){
			//std::cout<<" px: "<<anm->getx()<<" py: "<<anm->gety()<<" sx: "<<anm->getsx()<<" sy: "<<anm->getsy()<<": ";
			draw_polygon(anm->getx(),anm->gety(),anm->getsx(),anm->getsy(),tile,1);
			int ax = anm->getx();
			int ay = anm->gety();
			int mx = 10000;
			int my = 10000;
			int cmob = 21;
			for(int mob =0;mob<20;mob++){
				if(mobs[mob].isset()==0){
					continue;
				}
				if(mobs[mob].getx()<mx && mobs[mob].gety()<my){
					if(abs(mobs[mob].getx()-ax)<18 && abs(mobs[mob].gety()-ay)<18){
						mx = mobs[mob].getx();
						my = mobs[mob].gety();
						cmob = mob;
					}
				}	
			}
			if(cmob!=21 || anm->fin()){
				anm->check();
				mobs[cmob].deal_damage(anm->get_damage());
			}
		}
		else{
			anm->setanim(heroes[i].getx(),heroes[i].gety(),60,60);
		}
	}
}

void ask_mob_attack(){
	for(int i=0;i<20;i++){
		if(mobs[i].isset()==0){
			continue;
		}
		hit* anm = mobs[i].ask_attack();
		GLuint tile = anm->doStep();
		if(anm->is_check()==0 && anm->isset()){
			//std::cout<<" px: "<<anm->getx()<<" py: "<<anm->gety()<<" sx: "<<anm->getsx()<<" sy: "<<anm->getsy()<<": ";
			draw_polygon(anm->getx(),anm->gety(),anm->getsx(),anm->getsy(),tile,1);
			int ax = anm->getx();
			int ay = anm->gety();
			int mx = 10000;
			int my = 10000;
			int cmob = 21;
			for(int mob = 0;mob<20;mob++){
				if(heroes[mob].isset()==0){
					continue;
				}
				if(heroes[mob].getx()<mx && heroes[mob].gety()<my){
					if(abs(heroes[mob].getx()-ax)<18 && abs(heroes[mob].gety()-ay)<18){
						mx = heroes[mob].getx();
						my = heroes[mob].gety();
						cmob = mob;
					}
				}	
			}
			if(cmob!=21 || anm->fin()){
				anm->check();
				heroes[cmob].deal_damage(anm->get_damage());
			}
		}
		else{
			anm->setanim(mobs[i].getx(),mobs[i].gety(),60,60);
		}
	}
}
