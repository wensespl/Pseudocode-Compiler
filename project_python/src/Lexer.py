from ply import lex


class Lexer(object):

    def build(self):
        self.lexer = lex.lex(object=self)
        
    def input(self, text):
        self.lexer.input(text)
        
    def token(self):
        self.last_token = self.lexer.token()
        return self.last_token
    
    def test(self, text):
        self.input(text)
        while True:
            tok = self.lexer.token()
            if not tok: 
                break
            print(tok)

    reserved = {
        'ENTERO': 'INT',
        'DECIMAL': 'DOUBLE',
        'ENTRADA': 'INPUT',
        'SALIDA': 'OUTPUT',
        'SUBRUTINA': 'SUBROUTINE',
        'FINSUBRUTINA': 'ENDSUBROUTINE',
        'DEVOLVER': 'RETURN',
        'SI': 'IF',
        'ENTONCES': 'THEN',
        'SINO': 'ELSE',
        'FINSI': 'ENDIF',
        'MIENTRAS': 'WHILE',
        'HACER': 'DO',
        'FINMIENTRAS': 'ENDWHILE',
        'PARA': 'FOR',
        'HASTA': 'TO',
        'FINPARA': 'ENDFOR',
    }

    tokens = [
        'VAR',
        'INT_CONST', 'DOUBLE_CONST', 'STRING_CONST',
        'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'EQUALS', 'PERCENT',
        'COMMA', 'NEWLINE',
        'LPAREN', 'RPAREN',
        'LBRACKET', 'RBRACKET',
        'LESS_THAN', 'LESS_EQUAL',
        'GREATER_THAN', 'GREATER_EQUAL',
        'EQUALITY', 'NOT_EQUALITY'
    ] + list(reserved.values())

    t_PLUS = r'\+'
    t_MINUS = r'-'
    t_TIMES = r'\*'
    t_DIVIDE = r'/'
    t_EQUALS = r'='
    t_PERCENT = r'%'

    t_LESS_THAN = r'<'
    t_LESS_EQUAL = r'<='
    t_GREATER_THAN = r'>'
    t_GREATER_EQUAL = r'>='
    t_EQUALITY = r'=='
    t_NOT_EQUALITY = r'<>'

    t_LPAREN = r'\('
    t_RPAREN = r'\)'
    t_LBRACKET = r'\['
    t_RBRACKET = r'\]'

    t_COMMA = r'\,'

    t_ignore = " \t"
    t_ignore_COMMENT = r'\#.*'

    def t_VAR(self, t):
        r'[a-zA-Z_][a-zA-Z0-9_]*'
        t.type = self.reserved.get(t.value, 'VAR')
        return t

    def t_DOUBLE_CONST(self, t):
        r'\d+\.\d*'
        t.value = float(t.value)
        return t

    def t_INT_CONST(self, t):
        r'\d+'
        t.value = int(t.value)
        return t

    def t_STRING_CONST(self, t):
        r'".*?"'
        t.value = t.value[1:len(t.value)-1]
        return t

    def t_NEWLINE(self, t):
        r'\n+'
        t.lexer.lineno += t.value.count("\n")
        return t

    def t_error(self, t):
        print(f"Illegal character {t.value[0]!r}")
        t.lexer.skip(1)


if __name__ == "__main__":
    input_file = open(".\examples\code.spl")
    lines = [line.lstrip()
             for i, line in enumerate(input_file) if line.strip()]
    lines[-1] = lines[-1].rstrip()
    input_file.close()

    text = ''.join(lines)
    
    lexer = Lexer()
    lexer.build()
    lexer.test(text)
