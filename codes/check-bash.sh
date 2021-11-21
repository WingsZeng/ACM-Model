#!/bin/bash
let i=1
while true; do
    echo $i | ./X-data > X.in
    ./X < X.in > X.out
    ./X-bf < X.in > X-bf.out
    if diff X.out X-bf.out; then
        echo $i AC
    else
        echo $i WA
        cat X.in
        exit 0
    fi
    let i=i+1
done
