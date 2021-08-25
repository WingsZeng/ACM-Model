while true; do
    ./X-data > ./X.in
    ./X < ./X.in > ./X.out
    ./X-bf < ./X.in > ./X-bf.out
    if diff ./X.out ./X-bf.out; then
    	printf "AC\n"
    else
        printf "WA\n"
        cat ./X.in
        exit 0
    fi
done
