std::vector<std::vector<float> >  current_font;
void load_font(const char * filename){
	FILE * file;
	file = fopen( filename, "rb" );
	//std::cout<<" file! ";
	if ( file == NULL ) {
		std::cout<<filename<<"\n";
		return;
	}
	char header[4];
	fseek(file,0,SEEK_SET);
	fread(header,1,4,file);
	std::cout<<"\nfont:\n";
	int ok_header=1;
	//checking if header is 0100
	for(int i=0;i<4;i++){
		if(i==1 && (int)header[i]!=1){
			ok_header=0;
			break;
		}
		if(i!=1 && (int)header[i]!=0){
			ok_header=0;
			break;
		}
	}
	if(ok_header!=1){
		std::cout<<"bad_font";
		return;
	}
	//get number of tables in ttf file
	char tables[2];
	int tables_i;
	fseek(file,4,SEEK_SET);
	fread(tables,1,2,file);
	if((int)tables[0]==0){
		tables_i=(int)tables[1];
	}
	else{
		tables_i=(int)tables[0]*256+(int)tables[1];
	}
	std::cout<<"tables: "<<tables_i<<"\n";
	
	
	
	
	
}
