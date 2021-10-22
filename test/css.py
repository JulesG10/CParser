import re
import sys

def get_nospace(index: int, text: str):
    for n in range(index, len(text)):
        if text[n] != ' ':
            index = n
            break
    return index

def get_param(index: int, text: str):
    validparam = re.compile('[a-zA-Z\"\.]+')
    name = ""
    i = index
    for k in range(index, len(text)):
        if validparam.match(str(text[k])) != None:
            name += str(text[k])
            i += 1
        else:
            break

    return (name, i)

def get_text(index: int, text: str):
    validname = re.compile('[a-zA-Z]+')
    name = ""
    i = index
    for k in range(index, len(text)):
        if validname.match(str(text[k])) != None:
            name += str(text[k])
            i += 1
        else:
            break

    return (name, i)


def get_string(index:int,text:str):
    string = ""
    i = get_nospace(index, text)
    if text[i] == "\"":
        i+=1

        for k in range(i, len(text)):
            if text[k] == "\"":
                i = k + 1
                break
            string += text[k]

    return (string,i)

def error(message):
    print("ERROR {0}".format(message))
    exit(1)

def error_syntax(message:str,text:str,index:int):
    print("ERROR  {0}  \"{1}\" at {2}".format(message,text, index))
    exit(1)

def parseInnerContext(index:int,text:str):
    i = index
    ctx = []

    for k in range(i,len(text)):
        i = get_nospace(i, text)

        name,i = get_text(i, text)
        if len(name) <= 0:
            error_syntax("Invalid inner context atttribute ", text[i], i)
        
        i = get_nospace(i, text)

        if text[i] == ":":
            i += 1
            i = get_nospace(i, text)
            
            key,i = get_text(i, text)

            i = get_nospace(i, text)

            if text[i] == ";":
                i+=1
                ctx.append((name,key))
                i = get_nospace(i, text)
                if text[i] == "}":
                    i += 1
                    break
            else:
                error_syntax(
                    "Require \";\" Invalid inner context atttribute ", text[i], i)
        else:
            error_syntax(
                "Require \":\" Invalid inner context atttribute ", text[i], i)
        
    

    return (ctx,i)

def parseFunctionParamValue(param:str):
    index = 0
    if param[0] == "\"" and param[len(param)-1] == "\"":
        return ['string', get_string(index, param)[0]]
    else:
        if get_text(index, param)[0] != param:
            error_syntax("Invalid function parameter", param, 0)
        else:
            return ['key', param]
        # if param.find("\"") != -1:
        #     error_syntax("Invalid function parameter", param, param.find("\""))
        # else:
        #     return ['key',param]

def parseAttributeValue(index,text):
    i = get_nospace(index, text)
    value = []
    if text[i] == "\"":
        v,i = get_string(i,text)
        value.append('string')
        value.append(v)
    elif text[i] == "{":
        i+=1
        ctx, i = parseInnerContext(i, text)
        value.append('inner')
        value.append(ctx)
    else:
        v,i = get_text(i,text)
        if text[i] == "(":
            i+=1
            func_data = []
            if text[i] == ")":
                i+=1
            else:
                for k in range(i,len(text)):
                    i = get_nospace(i,text)
                    
                    param, i = get_param(i,text)

                    if len(param) <= 0:
                        error_syntax("Invalid function ", text[i], i)

                    i = get_nospace(i, text)
                    
                    if text[i] == ")":
                        i +=1
                        func_data.append(parseFunctionParamValue(param))
                        break
                    elif text[i] == ",":
                        func_data.append(parseFunctionParamValue(param))
                    else:
                        error_syntax("Unknown character",text[k],k)
                    
                    i += 1
            
            value.append('function')
            value.append(func_data)
        else:
            value.append('key')
            value.append(v)

    return (i,value)

def parseAttribute(index:int,text:str,attribute_list:list[str] = []):
    i = get_nospace(index, text)

    name = ""
    name, i = get_text(i, text)
    if len(name) <= 0:
        error_syntax("Invalid attribute ", text[i], i)

    i = get_nospace(i, text)
    if text[i] == ':':
        i+=1

        i,value = parseAttributeValue(i,text)
        i = get_nospace(i, text)
        
        if text[i] == ';':
            i+=1
            attribute_list.append((name,value))
        else:
            error_syntax("Require \";\" Unknown character ", text[i], i)
    else:
        error_syntax("Require \":\" Unknown character ", text[i], i)

    return (i,attribute_list)
        


def parseContext(index:int,text:str,id_list:list[str] = []):
    i = get_nospace(index, text)
    if text[i] == '{':
        i+=1
        attribute_list = []
        for k in range(i, len(text)):
            if text[i] == '}':
                i+=1
                break
            i,_ = parseAttribute(i, text, attribute_list)
        return (i, attribute_list, id_list)
    else:
        error_syntax("Unknown character ", text[i], i)

def parseIdentifier(index: int, text: str, id_list: list[str] = []):
    i = get_nospace(index, text)

    if text[i] == '.':
        i += 1

        name = ""
        name, i = get_text(i, text)
        
        if len(name) <= 0:
            error_syntax("Invalid identifier ",text[i], i)
        else:
            id_list.append(name)

        i = get_nospace(i, text)
        if text[i] == ',':
            i += 1
            i = parseIdentifier(i, text, id_list)[0] # ref to list
        elif text[i] == '{':
            return (i, id_list)
        else:
            error_syntax("Unknown character", text[i], i)
    else:
        error_syntax("Unknown character ", text[i], i)

    return (i,id_list)


def parseIdentifierStyle(index,text):
    i, id_list = parseIdentifier(index, text, [])
    return parseContext(i, text, id_list)

def main(args):
    for file in args:
        with open(file) as f:
            cssScript = str.join("", f.readlines()).replace("\n", "").replace("\r", "")
            index = 0

            while True:
                index, ids, style = parseIdentifierStyle(index, cssScript)
                print(ids,style)

                index = get_nospace(index, cssScript)
                if index >= len(cssScript):
                    break

    return 0


if __name__ == "__main__":
    main(sys.argv[1:])
