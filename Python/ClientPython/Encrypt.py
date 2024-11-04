import random

def funcGetIndexEncrypt(letter, new_alph):
    index = 0
    while index < len(new_alph):
        if letter == new_alph[index]:
            return index
        index += 1
    return -1

def funcEncrypt(seed, text):
    def_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    new_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    enc_text = ""
    for i in range(52):
        buffer = new_alph[i]
        new_alph[i] = new_alph[seed[i]]
        new_alph[seed[i]] = buffer
    for i in range(len(text)):
        if text[i].isalpha():
            enc_text += def_alph[funcGetIndexEncrypt(text[i], new_alph)]
        else:
            enc_text += text[i]
    return enc_text

def funcGenerateSeed():
    seed = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51]
    random.shuffle(seed)
    return seed