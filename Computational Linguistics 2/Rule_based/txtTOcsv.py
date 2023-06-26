from textblob.classifiers import NaiveBayesClassifier

with open('pos_review.txt') as f:
    linespos = f.read().strip().split('_')

# print(lines)
l = []
for line in linespos:
    if line:
        l.append((line.decode('utf-8'), 'pos'))

with open('neg_review.txt') as f:
    linesneg = f.read().strip().split('_')

for line in linesneg:
    if line:
        l.append((line.decode('utf-8'), 'neg'))

cl = NaiveBayesClassifier(l)
print (cl.classify(line.decode('utf-8')))
