
def call_namespace(words):
    result = "namespace"
    for index in range(1, len(words)):
        result += ' ' + words[index] 
    return result
