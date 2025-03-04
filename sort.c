void InsertSort(int n, int A[n]){
    C = 0;
    M = 0;
    for(int i = 1; i < n; i ++){
        int temp = A[i];
        M++;
        int j = i - 1;
        while (j >= 0 && A[j] > temp){
            C++;
            A[j + 1] = A[j];
            M++;
            j--;
        }
        C++;
        A[j + 1] = temp;
        M++;
    }
}
