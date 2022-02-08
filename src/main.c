#include <stdio.h>
#include <stdlib.h>

#include "./libs/matrix.h"
#include "./libs/mymath.h"

void _print_student_average_grade(Matrix *grades, size_t student_index, Matrix *students)
{
    double average = mymath.average(grades);
    printf("Aluno %ld > %.0f\n", student_index + 1, mymath.ceil(average));
}

void _print_test_info(Matrix *grades, size_t test_index, Matrix *tests)
{
    printf(
        "Av %ld. %6.2f %6.2f\n",
        test_index + 1,
        mymath.average(grades),
        mymath.standard_deviation(grades));
}

int main()
{
    Matrix *students, *tests;
    int qt_students, qt_tests;

    students = matrix.create(2);
    tests = matrix.create(2);

    printf("Quantidade de alunos: ");
    scanf("%d", &qt_students);

    qt_students = CLAMP_MIN(qt_students, 0);

    printf("Quantidade de avaliações: ");
    scanf("%d", &qt_tests);

    qt_tests = CLAMP_MIN(qt_tests, 0);

    matrix.fill(students, qt_students);
    matrix.fill(tests, qt_tests);

    for (size_t test_index = 0; test_index < qt_tests; test_index++)
    {
        printf("\n-----\n");
        printf("Avaliação %ld\n", test_index + 1);

        for (size_t student_index = 0; student_index < qt_students; student_index++)
        {
            Matrix *student_grades, *test_grades, *adimensional_grade;
            int grade;

            printf("Aluno %ld > ", student_index + 1);
            scanf("%d", &grade);

            grade = CLAMP(grade, 0, 100);

            adimensional_grade = matrix.adimensional_create(grade);

            student_grades = matrix.get(students, student_index);
            matrix.append(student_grades, adimensional_grade);

            test_grades = matrix.get(tests, test_index);
            matrix.append(test_grades, adimensional_grade);
        }
    }

    printf("\n");
    printf("Resultado final\n");
    printf("Médias arredondadas para cima dos alunos: \n");

    matrix.foreach (students, _print_student_average_grade);

    printf("\n");
    printf("Média e desvio padrão (populacional) das avaliações: \n");

    int length = snprintf(NULL, 0, "%ld", matrix.length(tests));
    printf("%*c Média Desvio\n", 5 + length, ' ');

    matrix.foreach (tests, _print_test_info);

    return 0;
}