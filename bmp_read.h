GLuint LoadTexture( const char * filename )
{
	//std::cout<<"\n";
	//std::cout<<filename;
	GLuint texture;
	int width, height;
	unsigned char  data[49152];
	unsigned char  alphaed_data[65536];
	//std::cout<<" named! ";
	FILE * file;
	file = fopen( filename, "rb" );
	//std::cout<<" file! ";
	if ( file == NULL ) {
		std::cout<<filename<<"\n";
		return 0;
	}
	//getting header data
	unsigned long int searcher[2];
	char filetype[2];
	unsigned long int offset;
	//std::cout<<" named2 ";
	//checking if it is BMP
	fseek(file,0,SEEK_SET);
	fread(filetype,1,2,file);
	if(filetype[0]!='B' && filetype[1]!='M'){
		return 0;
	}
	rewind(file);
	//offset to image from header
	fseek(file,10,SEEK_SET); 
	fread(searcher,4,1,file);
	offset = searcher[0];
	rewind(file);
	//width and height
	fseek(file,18,SEEK_SET);
	fread(searcher,4,2,file);
	width = searcher[0];
	height = searcher[1];
	rewind(file);
	//std::cout<<width<<"/"<<height<<" "<<filename<<"\n";
	//image
	//setting offset
	fseek(file,offset,SEEK_SET);
	//getting image data
	//std::cout<<" size:"<<width*height*3;
	//data = new unsigned char [ width * height * 3 ];
	//std::cout<<" 0";
	fread( data, width * height * 3, 1, file );
	fclose( file );
	//unsigned char* alphaed_data = new unsigned char [ width * height * 4 ];;
	//std::cout<<" 0 ";
	//adding alpha/BGR->RGB
	for(int i = 0; i <= width * height ; ++i)
	{
		int dindex = i*3;
		int aindex = i*4;
		alphaed_data[aindex]=data[dindex+2]; 	//red
		alphaed_data[aindex+1]=data[dindex+1]; 	//green
		alphaed_data[aindex+2]=data[dindex];		//blue
		if(int(alphaed_data[aindex])==255 && int(alphaed_data[aindex+1])==255 && int(alphaed_data[aindex+2])==255){
			alphaed_data[aindex+3] = char(0);
		}
		else{
			alphaed_data[aindex+3] = char(255);
		}
		
	}
	//delete data;
	//std::cout<<"1";
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,0,GL_RGBA, GL_UNSIGNED_BYTE, alphaed_data );
	//std::cout<<"2";
	//free( data );
	//free( alphaed_data );
	//std::cout<<"3\n";
	return texture;
}
