#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int *nums, int numsSize)
{
    int *a = nums;
    int *b = a;
    while (b < nums + numsSize)
    {
        *a = *b;
        int *i = nums;
        for (; i < a; i++)
        {
            if (*i == *a)
                break;
        }
        if (i == a)
        {
            a++;
        }
        b++;
    }
    return a - nums;
}

int comp(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : 0;
}

void twoSum(int *nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), comp);
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    for (int i = 0; i < numsSize; i++)
    {
        //we need to check previous, why?
        //as previous is no result, then i am no result
        //because we are the same
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        int *left = &nums[i];
        int *right = nums + numsSize - 1;
        while (left < right)
        {
            if (*left + *right == 0)
            {
                printf("[%d,%d] ", *left, *right);
                break;
            }
            else if (*left + *right > 0)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), comp);
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    for (int i = 0; i < numsSize; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int *left = &nums[i] + 1;
        int *right = nums + numsSize - 1;
        while (left < right)
        {
            if (*left + *right + nums[i] == 0)
            {
                printf("[%d,%d,%d] ", nums[i], *left, *right);
                do
                {
                    left++;
                } while (*left == *(left - 1));
            }
            else if (*left + *right + nums[i] > 0)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int nums[] = {0, -3, 0, -1, 1, 0, -1, 2, 1, -1, -4, 4, 1, 1, 1, 0, 2, -2, 3, -2, 4, 2};
    printf("threeSum:");
    threeSum(nums, sizeof(nums) / sizeof(int), NULL, NULL);
    printf("\n");

    int nums1[] = {0, -3, 0, -1, 1, 0, -1, 2, 1, -1, -4, 4, 1, 1, 1, 0, 2, -2, 3, -2, 4, 2};
    printf("twoSum:");
    twoSum(nums1, sizeof(nums1) / sizeof(int));
    printf("\n");

    return 0;
}
