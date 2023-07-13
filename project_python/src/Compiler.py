from src.Parser import Parser
from src.ASTGraph import Grapher

if __name__ == "__main__":
    filename = "./examples/graphtest.spl"
    
    input_file = open(filename)
    lines = [line.lstrip() for _, line in enumerate(input_file) if line.strip()]
    lines[-1] = lines[-1].rstrip()
    input_file.close()

    text = ''.join(lines)
    
    ast = Parser().parse(text)
    
    Grapher().generate(ast)
    