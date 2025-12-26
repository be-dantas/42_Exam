#include <stdlib.h>

int *init_nums(int argc, char **argv)
{
    int i = 0;
    int *nums;

    nums = malloc(sizeof(int) * (argc - 2));
    if (!nums)
        return (NULL);
    while (i < (argc - 2))
    {
        nums[i] = atoi(argv[i + 2]);
        i++;
    }
    return (nums);
}

void print_nums(int *nums_print, int len)
{
    int i = 0;

    while (i < (len - 1))
    {
        printf("%d ", nums_print[i]);
        i++;
    }
    printf("%d\n", nums_print[i]);
}

void loop_soma(int *nums, int *nums_print, int len, int result, int i_nums, int i_nums_print, int soma)
{
    if (soma == result)
    {
        print_nums(nums_print, len);
        return ;
    }
    nums_print[i_nums_print] = nums[i_nums];
    loop_soma(nums, nums_print, len, result, i_nums + 1, i_nums_print + 1, soma + nums[i_nums]);
}

int main(int argc, char **argv)
{
    int *nums;
    int *nums_print;
    int result = atoi(argv[1]);
    
    if (argc < 2)
        return (0);

    nums = init_nums(argc, argv);
    if (!nums)
        return (1);
    nums_print = malloc(sizeof(int) * (argc - 2));
    if (!nums_print)
    {
        free(nums);
        return (1);
    }

    loop_soma(nums, nums_print, argc - 2, result, 0, 0, 0);
    free(nums);
    return (0);
}