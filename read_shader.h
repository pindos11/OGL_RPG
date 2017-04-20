const char * read_shader_file(const char* filename){
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL ) {
		std::cout<<filename<<"\n";
		return "";
	}
	std::string ostr;
	char c = fgetc(file);
	while(c!=EOF){
		ostr.append(1,c);
		c=fgetc(file);
	}
	return ostr.c_str();
}
