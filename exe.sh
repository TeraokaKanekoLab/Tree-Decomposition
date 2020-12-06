mdh() {
    echo "g++ src/mdh.cpp -o ./mdh --std=c++17"
    g++ src/mdh.cpp -o ./mdh --std=c++17
    echo "./mdh $1 $2"
    ./mdh $1 $2
    rm ./mdh
}

sbr() {
    echo "g++ src/sbr.cpp -o ./sbr --std=c++17"
    g++ src/sbr.cpp -o ./sbr --std=c++17
    echo "./sbr $1 $2"
    ./sbr $1 $2
    rm ./sbr
}

lmdh() {
    echo "g++ src/lmdh.cpp -o ./lmdh --std=c++17"
    g++ src/lmdh.cpp -o ./lmdh --std=c++17
    echo "./lmdh $1 $2"
    ./lmdh $1 $2
    rm ./lmdh
}

lmdh_sbr() {
    echo "g++ src/lmdh_sbr.cpp -o ./lmdh_sbr --std=c++17"
    g++ src/lmdh_sbr.cpp -o ./lmdh_sbr --std=c++17
    echo "./lmdh_sbr $1 $2"
    ./lmdh_sbr $1 $2
    rm ./lmdh_sbr
}

lmdh_naive() {
    echo "g++ src/lmdh_naive.cpp -o ./lmdh_naive --std=c++17"
    g++ src/lmdh_naive.cpp -o ./lmdh_naive --std=c++17
    echo "./lmdh_naive $1 $2"
    ./lmdh_naive $1 $2
    rm ./lmdh_naive
}

chart() {
    echo "python3 src/chart.py $1 $2"
    python3 src/chart.py $1 $2
    filename="charts/"$2"-"$1".pdf"
    open $filename
}

case $1 in
"mdh")
    mdh $2 $3
    ;;
"sbr")
    sbr $2 $3
    ;;
"lmdh")
    lmdh $2 $3
    ;;
"lmdh_sbr")
    lmdh_sbr $2 $3
    ;;
"lmdh_naive")
    lmdh_naive $2 $3
    ;;
"chart")
    chart $2 $3
    ;;
"all")
    mdh $2 $3
    sbr $2 $3
    lmdh $2 $3
    lmdh_naive $2 $3
    lmdh_sbr $2 $3
    chart $2 $3
    ;;
esac
