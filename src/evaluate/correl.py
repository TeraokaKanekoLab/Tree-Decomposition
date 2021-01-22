import sys

chart_type = sys.argv[1]
filename = sys.argv[2]
arg_width = sys.argv[3]
path = "output/" + chart_type + "/" + arg_width + "-" + filename + ".output"
f = open(path, "r")
lines = f.readlines()
X = []
Y = []
Y_X = []
for line in lines:
    line = line.split()
    x = float(line[0])
    y = float(line[1])
    X.append(x)
    Y.append(y)
    Y_X.append(y-x)
x_sum = sum(X)
y_sum = sum(Y)
num_elements = len(lines)
x_ave = x_sum / num_elements
y_ave = y_sum / num_elements
print("max(y-x) =", max(Y_X))
print("min(y-x) =", min(Y_X))
print("ave(y-x) =", sum(Y_X)/len(Y_X))
print("x_ave ==", x_ave)
print("y_ave ==", y_ave)
c = 0
px2 = 0
py2 = 0
for x, y in zip(X, Y):
    c += (x-x_ave) * (y-y_ave)
    px2 += (x-x_ave)**2
    py2 += (y-y_ave)**2
r = c/((px2*py2) ** 0.5)

c = 0
px2_XY = 0
py2_XY = 0
for x, y in zip(X, Y_X):
    c += (x-x_ave) * (y-y_ave)
    px2_XY += (x-x_ave)**2
    py2_XY += (y-y_ave)**2
r_XY = c/((px2_XY*py2_XY) ** 0.5)
print("r(X, Y) = " + str(r))
print("r(X, Y-X) = " + str(r_XY))
