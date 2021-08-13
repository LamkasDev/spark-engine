void sparkPrintPoints(SparkVector2* points) {
    int size = vector_size(points);
    printf("(START), ");
    for(int i = 0; i < size; i++) {
        SparkVector2 point = points[i];
        printf("(%f, %f), ", point.x, point.y);
    }
    printf("(END) \n");
}