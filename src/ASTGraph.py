import graphviz

from src import AST

class Grapher:
    
    def __init__(self):
        self.dot = None
        
    def generate(self, ast=[[]]):
        self.dot = graphviz.Graph("AST")

        for statement in ast[0]:
            self.graphgen(statement, self.dot)
            print(statement)

        self.dot.render(format='png')

    def graphgen(self, node, dot):

        if isinstance(node, AST.Constant):

            if node.dType == float:
                dot.node(str(node.value), 'float:'+str(node.value))

                return str(node.value)

            elif node.dType == int:
                dot.node(str(node.value), 'int:'+str(node.value))

                return str(node.value)

            elif node.dType == str:
                dot.node(node.value, 'str:'+node.value)

                return node.value

        elif isinstance(node, AST.Variable):

            if node.dType == float:
                dot.node(node.name, 'float:'+node.name)   
                
            elif node.dType == int:
                dot.node(node.name, 'int:'+node.name)

            elif node.dType == str:
                dot.node(node.name, 'str:'+node.name)

            return node.name

        # elif isinstance(node, AST.Array_Declaration):

        #     self.variables[(node.name, self.scope)] = node.dType

        #     r = node.elements

        #     if isinstance(r, AST.Variable) or isinstance(r, AST.Array_Element):
        #         rvalue = self.graphgen(r, builder)

        #         if r.dType == float or r.dType == int:
        #             rvalue = builder.load(rvalue,name=r.name + "_val",align=None)

        #     else:
        #         rvalue = self.graphgen(r, builder)

        #     if node.dType == int:
        #         raw = builder.call(self.malloc, [rvalue], name=node.name+"_raw")
        #         builder.bitcast(raw, ir.PointerType(ir.IntType(32), addrspace=0), name=node.name)

        #     elif node.dType == float:
        #         raw = builder.call(self.malloc, [rvalue], name=node.name+"_raw")
        #         builder.bitcast(raw, ir.PointerType(ir.DoubleType(), addrspace=0), name=node.name)

        #     return builder

        # elif isinstance(node, AST.Array_Element):

        #     if node.dType == int:
        #         ptr_type = ir.PointerType(ir.IntType(32), addrspace=0)
        #     elif node.dType == float:
        #         ptr_type = ir.PointerType(ir.DoubleType(), addrspace=0)

        #     index = self.graphgen(node.index, builder)

        #     if isinstance(node.index, AST.Variable) or isinstance(node.index, AST.Array_Element):
        #         index = builder.load(index,name="_val",align=None)

        #     arr = ptr_type('%"'+node.name+'"')
        #     index_ptr = builder.gep(arr, [index], name="element")

        #     return index_ptr

        elif isinstance(node, AST.Assignment):

            l, r = node.children()

            lvalue = self.graphgen(l, dot)
            rvalue = self.graphgen(r, dot)
            
            dot.edge(lvalue, rvalue)
            
            return 

        # elif isinstance(node, AST.BinaryOp):

        #     cmp_op = {">","<","!=",">=",'<=',"=="}

        #     l, r = node.children()

        #     if isinstance(l, AST.Variable) or isinstance(l, AST.Array_Element):
        #         lvalue = self.graphgen(l, builder)

        #         if l.dType == float or l.dType == int:
        #             lvalue = builder.load(lvalue,name=l.name + "_val",align=None)

        #     else:
        #         lvalue = self.graphgen(l, builder)

        #     if isinstance(r, AST.Variable) or isinstance(r, AST.Array_Element):
        #         rvalue = self.graphgen(r, builder)

        #         if r.dType == float or r.dType == int:
        #             rvalue = builder.load(rvalue,name=r.name + "_val",align=None)

        #     else:
        #         rvalue = self.graphgen(r, builder)

        #     if l.dType == float and r.dType == int:
        #         rvalue = builder.sitofp(rvalue, ir.DoubleType(), name="_casted")

        #     elif l.dType == int and r.dType == float:
        #         lvalue = builder.sitofp(lvalue, ir.DoubleType(), name="_casted")

        #     if node.op == '+':

        #         if node.dType == str:

        #             res = builder.call(self.malloc, [ir.IntType(32)(node.length)], name="pt1")
        #             builder.call(self.memcpy, [res, lvalue, ir.IntType(32)(l.length - 1)])
        #             pt2 = builder.gep(res, [ir.IntType(32)(l.length - 1)], "pt2")
        #             builder.call(self.memcpy, [pt2, rvalue, ir.IntType(32)(r.length)])

        #         elif node.dType == float:
        #             res = builder.fadd(lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.add(lvalue, rvalue, name="t")

        #     elif node.op == '-':
        #         if node.dType == float:
        #             res = builder.fsub(lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.sub(lvalue, rvalue, name="t")

        #     elif node.op == '*':
        #         if node.dType == float:
        #             res = builder.fmul(lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.mul(lvalue, rvalue, name="t")

        #     elif node.op == '/':
        #         if node.dType == float:
        #             res = builder.fdiv(lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.sdiv(lvalue, rvalue, name="t")

        #     elif node.op == '%':
        #         if node.dType == float:
        #             res = builder.frem(lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.srem(lvalue, rvalue, name="t")

        #     elif node.op in cmp_op:

        #         if node.dType == float:
        #             res = builder.fcmp_unordered(node.op, lvalue, rvalue, name="t")

        #         elif node.dType == int:
        #             res = builder.icmp_signed(node.op, lvalue, rvalue, name="t")

        #     return res

        # elif isinstance(node, AST.UnaryOp):

        #     r = node.right

        #     if isinstance(r, AST.Variable) or isinstance(r, AST.Array_Element):
        #         rvalue = self.graphgen(r, builder)

        #         if r.dType == float or r.dType == int:
        #             rvalue = builder.load(rvalue,name=r.name + "_val",align=None)

        #     else:
        #         rvalue = self.graphgen(r, builder)

        #     if node.op == '-':

        #         if r.dType == int: 
        #             res = builder.neg(rvalue)

        #         elif r.dType == float:
        #             res = builder.fsub(ir.DoubleType()(0),rvalue)

        #     return res

        # elif isinstance(node, AST.Output):

        #     raw_data = node.children()

        #     data = self.graphgen(raw_data, builder)

        #     if isinstance(raw_data, AST.Array_Element):
        #         data = builder.load(data,name=raw_data.name + "_val",align=None)

        #     if raw_data.dType == float: 
        #         fmt_ptr = builder.gep(self.double_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #         if isinstance(raw_data, AST.Variable):
        #             data = builder.load(data,name=raw_data.name + "_val",align=None)

        #     elif raw_data.dType == str:
        #         fmt_ptr = builder.gep(self.string_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #     elif raw_data.dType == int:
        #         fmt_ptr = builder.gep(self.int_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #         if isinstance(raw_data, AST.Variable):
        #             data = builder.load(data,name=raw_data.name + "_val",align=None)

        #     builder.call(self.printf, [fmt_ptr, data], name="print")
                
        #     fmt_ptr = builder.gep(self.newline_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")
        #     builder.call(self.printf, [fmt_ptr], name="print")

        #     return builder

        # elif isinstance(node, AST.If):

        #     condition, if_true, if_false = node.children()

        #     condition = self.graphgen(condition, builder)

        #     if if_false == None:

        #         with builder.if_then(condition) as then:
        #             for statement in if_true:
        #                 builder = self.graphgen(statement, builder)

        #     else:   
        #         with builder.if_else(condition) as (then, otherwise):

        #             with then:
        #                 for statement in if_true:
        #                     builder = self.graphgen(statement, builder)


        #             with otherwise:
        #                 for statement in if_false:
        #                     builder = self.graphgen(statement, builder)

        #     return builder

        # elif isinstance(node, AST.While):

        #     condition, body = node.children()

        #     loop_body = self.scope.append_basic_block(name="while.body")

        #     builder.branch(loop_body)
        #     loop_body_builder = ir.IRBuilder(loop_body)

        #     for statement in body:
        #         loop_body_builder = self.graphgen(statement, loop_body_builder)
            
        #     condition = self.graphgen(condition, loop_body_builder)

        #     loop_exit = self.scope.append_basic_block(name="while.exit")
        #     loop_exit_builder = ir.IRBuilder(loop_exit)

        #     loop_body_builder.cbranch(condition, loop_body, loop_exit)

        #     return loop_exit_builder
        
        # elif isinstance(node, AST.For):
          
        #     assignment, final, body = node.children()
        #     variable, _ = assignment.children()
            
        #     assignment = self.graphgen(assignment, builder)
        #     var = self.graphgen(variable, builder)
            
        #     loop_body = self.scope.append_basic_block(name="for.body")
            
        #     builder.branch(loop_body)
        #     loop_body_builder = ir.IRBuilder(loop_body)
            
        #     current_i_value = loop_body_builder.load(var,name=variable.name+"_t",align=None)
            
        #     for statement in body:
        #         loop_body_builder = self.graphgen(statement, loop_body_builder)
            
        #     new_i_value = loop_body_builder.add(current_i_value, ir.IntType(32)(1), name="t")
        #     loop_body_builder.store(new_i_value, var)
            
        #     final = self.graphgen(final, loop_body_builder)
        #     condition = loop_body_builder.icmp_signed('<', new_i_value, final, name="t")
            
        #     loop_exit = self.scope.append_basic_block(name="for.exit")
        #     loop_exit_builder = ir.IRBuilder(loop_exit)

        #     loop_body_builder.cbranch(condition, loop_body, loop_exit)

        #     return loop_exit_builder
        
        # elif isinstance(node, AST.Input):
        
        #     variable = self.graphgen(node.variable, builder)

        #     #builder.call(self.realloc, [variable, ir.IntType(32)(5)]) for strings
        #     self.variables[(node.variable.name, self.scope)] = 0

        #     if node.dType == int:
        #         fmt_ptr = builder.gep(self.int_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #     elif node.dType == float:
        #         fmt_ptr = builder.gep(self.double_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #     elif node.dType == str:
        #         fmt_ptr = builder.gep(self.string_fmt, [ir.IntType(32)(0), ir.IntType(32)(0)], inbounds=False, name="fmt_ptr")

        #     builder.call(self.scanf, [fmt_ptr, variable], name="scan")

        #     return builder
        
        # elif isinstance(node, AST.Function_Decl):
            
        #     args = []
            
        #     for arg in node.args:
        #         if arg[1] == int:
        #             args.append(ir.IntType(32))
                
        #         elif arg[1] == float:
        #             args.append(ir.DoubleType())
                    
        #     if node.dType == int:
        #         dType = ir.IntType(32)
                
        #     elif node.dType == float:
        #         dType = ir.DoubleType()
                    
        #     fnty = ir.FunctionType(dType, args)
            
        #     func = ir.Function(self.module, fnty, name=node.name)
                           
        #     self.variables[(node.name, self.scope)] = dType
        #     self.functions[node.name] = func
            
        #     for i in range(0, len(func.args)):
        #         func.args[i].name = node.args[i][0] + "_arg"
            
        #     block = func.append_basic_block(name="entry")
        #     func_builder = ir.IRBuilder(block)
            
        #     self.scope = func
            
        #     for i in range(0, len(node.args)):
        #         arg = node.args[i]
                
        #         if arg[1] == int:
        #             dType = ir.IntType(32)

        #         elif arg[1] == float:
        #             dType = ir.DoubleType()
                    
        #         var = func_builder.alloca(dType,size=None,name=arg[0])
        #         func_builder.store(func.args[i],var,align=None)
            
        #     for statement in node.body:
        #         func_builder = self.graphgen(statement, func_builder)
            
        #     if not func_builder.block.is_terminated:
        #         if node.dType == int:
        #             dType = ir.IntType(32)
        #             func_builder.ret(dType(0))

        #         elif node.dType == float:
        #             dType = ir.DoubleType()
        #             func_builder.ret(dType(0.0))
            
        #     self.scope = self.main
            
        #     return builder
    
        # elif isinstance(node, AST.Function_Call):
            
        #     func = self.functions[node.name]
            
        #     args = []
            
        #     for arg in node.args:
                
        #         built_arg = self.graphgen(arg, builder)
                
        #         if isinstance(arg, AST.Array_Element) or isinstance(arg, AST.Variable):
        #             built_arg = builder.load(built_arg,name=arg.name + "_val",align=None)
                    
        #         args.append(built_arg)
            
        #     res = builder.call(func, args, name=node.name + '_call')
            
        #     return res 
        
        # elif isinstance(node, AST.Return):
            
        #     res = self.graphgen(node.data, builder)
            
        #     if isinstance(node.data, AST.Array_Element) or isinstance(node.data, AST.Variable):
        #         res = builder.load(res,name="res",align=None)
            
        #     builder.ret(res)
            
        #     return builder