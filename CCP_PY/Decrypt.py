def funcGetIndexDecrypt(letter, def_alph):
    index = 0
    while index < len(def_alph):
        if letter == def_alph[index]:
            return index
        index += 1
    return -1

def funcDecrypt(seed, text):
    def_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    new_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
    enc_text = ""
    for i in range(26):
        buffer = new_alph[i]
        new_alph[i] = new_alph[seed[i]]
        new_alph[seed[i]] = buffer
    for i in range(len(text)):
        if text[i].isalpha():
            enc_text += new_alph[funcGetIndexDecrypt(text[i], def_alph)]
        else:
            enc_text += text[i]
    return enc_text