const fs = require('fs');

function lexer(str) {
  this.getToken = (type, value) => {return {type: type, value: value}};

  this.isEmpty = (char) => char == '\n' || char == '\r' || char == ' ';
  this.isIdentifiy = (char) => char >= "가" && char <= "힣";
  this.isSpecifiy = (char) => char >= "ㄱ" && char <= "ㅎ";
  this.isNumber = (char) => char >= "0" && char <= "9";

  this.stringList = [...str];

  this.index = 0;
  this.getChar = () => {
    while (this.stringList.length > this.index 
           && this.isEmpty(this.stringList[this.index])) { this.index++; }

    if (this.stringList.length < this.index) return undefined;

    return this.stringList[this.index++];
  }
  this.getSequenceToken = (tokenType, check) => {
    let tokenString = "";

    while (check(this.char)) {
      tokenString += this.char;
      this.char = this.getChar();
    }

    this.tokens.push(this.getToken(tokenType, tokenString));
  }
  this.getSingleToken = (str, tokenType) => {
    this.tokens.push(this.getToken(tokenType, str));
    this.char = this.getChar();
  }

  this.tokens = [];

  this.char = this.getChar();

  while (1) {
    // 토큰 목록 반환
    if (!this.char) return this.tokens;
    
    if (this.isIdentifiy(this.char)) { // identifiy : 식별자
      this.getSequenceToken("identifiy", this.isIdentifiy);
      continue;
    }
    if (this.isSpecifiy(this.char)) { // specifiy : 예약어
      this.getSequenceToken("specifiy", this.isSpecifiy);
      continue;
    }
    if (this.isNumber(this.char)) { // number : 뭔지 모르냐?
      let tokenString = "";

      while (this.isNumber(this.char)) {
        tokenString += this.char;
        this.char = this.getChar();
      }
      if (this.char === ".") {
        tokenString += this.char;
        this.char = this.getChar();
        while (this.isNumber(this.char)) {
          tokenString += this.char;
          this.char = this.getChar();
        }
      }
      this.tokens.push(this.getToken("number", tokenString));
      continue;
    }
    if (this.char === "'" || this.char === '"') {
      let compareChar = this.char;
      this.char = this.getChar();
      this.getSequenceToken("string", (c) => c != compareChar);
      this.char = this.getChar();
      continue;
    }

    // 특수문자 처리
    switch (this.char) {
      case ":":
        if (this.stringList[this.index] === "=") {
          this.index++;
          this.getSingleToken(":=", "assignment");
        } else {
          console.error("':' 인 토큰은 아직 존재하지 않습니다.");
          return null;
        }
        break;
      case ".":
        // todo : number token
        this.getSingleToken(".", "dot");
        break;
      case ",":
        this.getSingleToken(",", "comma");
        break;
      case "=":
        this.getSingleToken("=", "equal");
        break;
      case "&":
        this.getSingleToken("&", "and");
        break;
      case "|":
        this.getSingleToken("|", "or");
        break;
      case "+":
        this.getSingleToken("+", "add");
        break;
      case "-":
        // todo : number token
        this.getSingleToken("-", "subtract");
        break;
      case "*":
        this.getSingleToken("*", "multiply");
        break;
      case "/":
        this.getSingleToken("/", "divide");
        break;
      case "<":
        this.getSingleToken("<", "less than");
        break;
      case ">":
        this.getSingleToken(">", "greater than");
        break;
      case "{":
        this.getSingleToken("{", "left brace");
        break;
      case "}":
        this.getSingleToken("}", "right brace");
        break;
      case "(":
        this.getSingleToken("(", "left paren");
        break;
      case ")":
        this.getSingleToken(")", "right paren");
        break;
      default:
        console.error(this.char + " 토큰 없다고 전해라");
        return null;
    }
  }

  console.error("while 문에서 빠져나왔다고?");
  return null;
}

fs.readFile('./exam/plus.um', 'utf-8', (err, data) => {
  if (err) {
    return console.error(err);
  }
  tokens = lexer(data);

  console.log(tokens);
});