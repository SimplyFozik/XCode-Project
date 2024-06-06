import random

def funcGetIndexEncrypt(letter, new_alph):
    index = 0
    while index < len(new_alph):
        if letter == new_alph[index]:
            return index
        index += 1
    return -1

def funcEncrypt(seed, text):
    def_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    new_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    enc_text = ""
    for i in range(26):
        buffer = new_alph[i]
        new_alph[i] = new_alph[seed[i]]
        new_alph[seed[i]] = buffer
    for i in range(len(text)):
        if text[i].isalpha():
            enc_text += def_alph[funcGetIndexEncrypt(text[i], new_alph)]
        else:
            enc_text += text[i]
    return enc_text

def funcGenerateSeed(text):
    seed = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25]
    random.shuffle(seed)
    print(seed)
    return funcEncrypt(seed,text)