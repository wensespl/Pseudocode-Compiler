from Parser import Parser
from IRGenerator import Generator

if __name__ == "__main__":
    filename = "./examples/codefor.spl"
    output = "output.ll"
    
    input_file = open(filename)
    lines = [line.lstrip() for i, line in enumerate(input_file) if line.strip()]
    lines[-1] = lines[-1].rstrip()
    input_file.close()

    text = ''.join(lines)
    
    ast = Parser().parse(text)
        
    ir = Generator().generate(ast, output)
    
    output_file = open(output,"w+")
    output_file.write(str(ir))
    output_file.close()