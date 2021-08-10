const fs = require('fs');
const lexer = require('./lib/lexer');
const parser = require('./lib/parser');

fs.readFile('./exam/plus.um', 'utf-8', (err, data) => {
  if (err) {
    return console.error(err);
  }
  tokens = lexer(data);

  console.log(tokens);

  //ast = parser(tokens);
});