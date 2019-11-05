import sys
import gensim.models as word2vec

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print('Usage: {} {} {}'.format(sys.argv[0],'.ptxt', 'question'))
    else:
        infile = open(sys.argv[1], 'r')
        pgm = infile.readline().strip()

        while(pgm.find("<c>") == -1):
            pgm = infile.readline().strip()

        ko_model = word2vec.Word2Vec.load('./ko.bin')
        question = sys.argv[2]
        dist1 = -1
        dist2 = -1
        res1 = ""
        res2 = ""
        while(pgm.find("</c>") == -1):
            pgm = infile.readline().strip()
            distance = ko_model.wv.wmdistance(question, pgm)
            if(dist1 == -1 or distance < dist1):
                dist1 = distance
                res1 = pgm
            elif(dist2 == -1 or distance < dist2):
                dist2 = distance
                res2 = pgm
            elif(pgm.find(question) != -1):
                dist1 = 0
                res1 = pgm

        infile.close()
        outfile = open('sentence.txt','w')
        outfile.write(res1+res2)
        outfile.close()
