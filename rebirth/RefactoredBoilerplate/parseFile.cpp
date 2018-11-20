enum Token {
	Number,
  OpenBracket,
  CloseBracket,
  Light,
  Sphere,
  Triangle,
  Plane
}
class Tokenizer {
	public:
	Tokenizer(std::fstream file) {
  	f = file;
  }
  
  Token getNextToken() {
  	std::string s;
    skip:
  	while((char c = f.get()) != EOF || (c != ' ') || (c != '\n'))  {
    	s.push_back(c);
    }
    if(s[0] == '#')
    	goto skip;
    if(s == "{") 
    	return OpenBracket;
    if(s == "}") 
    	return CloseBracket;
    if(s == "light")
    	return Light;
    if(s == "sphere")
    	return Sphere;
    if(s == "triangle")
    	return Triangle;
    if(s == "plane")
    	return Plane;
    bool isnum = true;
    for(char c : s){
    	if((c != ".") && (!isdigit(c)))
      isnum = false;
    }
    if(!isnum) {
    	return (Token)-1;
    }
    v = stof(s);
    return Number;
  }
  
  float getValue() {
  	return v;
  }
  
  private:
  float v;
  std::fstream f;
  
}

class Parser {
	Parser(Tokenizer tok) {
   t = tok;
  }
  
  
  private:
  Tokenizer t;
}
