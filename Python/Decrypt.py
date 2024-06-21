def funcGetIndexDecrypt(letter, def_alph):
    index = 0
    while index < len(def_alph):
        if letter == def_alph[index]:
            return index
        index += 1
    return -1

def funcDecrypt(seed, text):
    counter = 0
    intseed = [0] * 52

    i = 0
    while i < len(seed):  # Fix: Correctly use len(seed) instead of len[seed]
        if seed[i].isdigit():  # Check if the current character in seed is a digit
            start = i
            while i < len(seed) and seed[i].isdigit():  # Continue while the character is a digit
                i += 1
            end = i
            intseed[counter] = int(seed[start:end])
            counter += 1
        else:
            i += 1

    def_alph = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    new_alph = list(def_alph)  # Create a copy of def_alph for new_alph

    # Swap characters in new_alph based on intseed
    for i in range(52):
        buffer = new_alph[i]
        new_alph[i] = new_alph[intseed[i]]
        new_alph[intseed[i]] = buffer

    enc_text = ""
    for char in text:
        if char.isalpha():
            enc_text += new_alph[funcGetIndexDecrypt(char, def_alph)]
        else:
            enc_text += char

    return enc_text