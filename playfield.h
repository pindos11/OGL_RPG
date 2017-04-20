#define VISIBLE_FIELD_SIZEX 60
#define VISIBLE_FIELD_SIZEY 60
#define FIELD_TILE_SIZE 20


class fpos{
	private:
		int x;
		int y;
		int walkable;
		int texture;
	public:
		void set(int ix, int iy, int itexture, int iwalkable){
			x = ix;
			y = iy;
			texture = itexture;
			walkable = iwalkable;
		}
		int can_walk(){
			return walkable;
		}
		int get_texture(){
			return texture;
		}
};
class field{
	private:
		fpos parts[VISIBLE_FIELD_SIZEX][VISIBLE_FIELD_SIZEY];
		int posx;
		int posy;
		int type;
	public:
		field(){
			type = randint(1,2);
			srand(time(0));
			for(int i=0;i<VISIBLE_FIELD_SIZEX;i++){
				for(int j=0;j<VISIBLE_FIELD_SIZEY;j++){
					parts[i][j].set(i+1,j+1,1,1);
					}
				}
			
			int obsts = randint(9,15);
			for(int i = 0;i<obsts;i++){
				int osx = randint(6,9);
				int osy = randint(6,9);
				int px = randint(5,VISIBLE_FIELD_SIZEX-5-osx);
				int py = randint(5,VISIBLE_FIELD_SIZEY-5-osy);
				for(int x = px;x<px+osx;x++){
					for(int y = py;y<py+osy;y++){
						if(x==px || y==py || x==px+osx-1 || y==py+osy-1){
							if(parts[x][y].can_walk()){
								parts[x][y].set(x+1,x+1,3,1);
							}
							else{
								parts[x][y].set(x+1,x+1,4,0);
							}
						}
						else{
							parts[x][y].set(x+1,x+1,4,0);
						}
						
					}
				}
			}
		}
		
		int get_part_texture(int x, int y){
			return parts[x][y].get_texture();
		}
		int can_walk(int x,int y){
			return parts[x][y].can_walk();
		}
		int getx(){
			return posx;
		}
		int gety(){
			return posy;
		}
		int setxy(int px, int py){
			posx = px;
			posy = py;
		}
};
std::vector<field> game_field;
field curf;
void add_field(int px,int py){
	field a;
	a.setxy(px,py);
	game_field.push_back(a);
	curf = game_field.back();
	curfpx = px;
	curfpy = py;
}

void draw_field(){
	int ftextures[]={1,0,2,1,3,5,4,6};
	int flen = 8; //len of ftextures
	for(int i=0;i<VISIBLE_FIELD_SIZEX;i++){
		for(int j=0;j<VISIBLE_FIELD_SIZEY;j++){ 
			int ctex = 0;
			int ftex = curf.get_part_texture(i,j);
			for(int tex=0;tex<flen;tex+=2){
				if(ftextures[tex]==ftex){
					ctex = ftextures[tex+1];
					break;
				}
			}
			draw_polygon(i*FIELD_TILE_SIZE+FIELD_TILE_SIZE/2,j*FIELD_TILE_SIZE+FIELD_TILE_SIZE/2,FIELD_TILE_SIZE,FIELD_TILE_SIZE,textures[ctex],1);
		}
	}
}
