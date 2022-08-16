#pragma once
#include<vector>
using namespace std;

const int M = 999999999;

using SDF_TYPE = double;

struct vec2
{
    int x;
    int y;
};

void DiscreteSDF2D(/*vector<vector<SDF_TYPE>>& vec3_in, */vector<vector<SDF_TYPE>>& vec3_out, int row, int col, vector<vector<vec2>>& min_dist_pts)
{
    std::vector<std::vector<int>> vec2_x(row, std::vector<int>(col, M));
    std::vector<std::vector<int>> vec2_y(row, std::vector<int>(col, M));

    std::vector<std::vector<int>> vec2_x_flag(row, std::vector<int>(col, 0));
    std::vector<std::vector<int>> vec2_y_flag(row, std::vector<int>(col, 0));

    //标记边界
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (vec3_out[i][j] == 0)
            {
                vec2_x[i][j] = 0;
                vec2_y[i][j] = 0;
            }
        }
    }

    //一维计算 new
    //mostRight
    for (int i = 0; i < row; i++)
    {
        //vec2x[i][0]=M;
        for (int j = 1; j < col; j++)
        {
            if (vec3_out[i][j] != 0)
            {
                vec2_x[i][j] = vec2_x[i][j - 1] + 1;
                vec2_x_flag[i][j] = -1;
            }
        }
    }
    //mostLeft
    for (int i = 0; i < row; i++)
    {
        //vec2x[i][col-1]=M;
        for (int j = col - 2; j >= 0; j--)
        {
            if (vec3_out[i][j] != 0)
            {
                //vec2_x[i][j] = std::min(vec2_x[i][j], vec2_x[i][j + 1] + 1);
                if (vec2_x[i][j] > vec2_x[i][j + 1] + 1)
                {
                    vec2_x[i][j] = vec2_x[i][j + 1] + 1;
                    vec2_x_flag[i][j] = 1;
                }
            }
        }
    }
    //mostUp    不应该包含自身
    for (int j = 0; j < col; j++)
    {
        //vec2y[row-1][j]=M;
        for (int i = row - 2; i >= 0; i--)
        {
            if (vec3_out[i][j] != 0)
            {
                vec2_y[i][j] = vec2_y[i + 1][j] + 1;
                vec2_y_flag[i][j] = 1;
            }
        }
    }
    //mostDown
    for (int j = 0; j < col; j++)
    {
        //vec2y[0][j]=M;
        for (int i = 1; i < row; i++)
        {
            if (vec3_out[i][j] != 0)
            {
                //vec2_y[i][j] = std::min(vec2_y[i][j], vec2_y[i - 1][j] + 1);
                if (vec2_y[i][j] > vec2_y[i - 1][j] + 1)
                {
                    vec2_y[i][j] = vec2_y[i - 1][j] + 1;
                    vec2_y_flag[i][j] = -1;
                }
            }
        }
    }
    //二维计算
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            /*if (vec2x[i][j] == 0 || vec2y[i][j] == 0)
            {
                vec3_out[i][j][curhei1] = 0;
                continue;
            }*/
            if (vec3_out[i][j] == 0)
            {
                continue;
            }
            /*if (curhei1 - 1 >= 0 && vec3_in[i][j][curhei1 - 1] == 0)
            {
                vec3_out[i][j][curhei1] = 0;
                continue;
            }
            if (curhei1 + 1 < hei && vec3_in[i][j][curhei1 + 1] == 0)
            {
                vec3_out[i][j][curhei1] = 0;
                continue;
            }*/
            if (j == 0)
            {
                int minPOW = M/*vec2_x[i][j] * vec2_x[i][j]*/;
                int min_i = -1;
                int min_j = -1;
                for (int ii = 0; ii < row; ii++)
                {
                    int temp = (i - ii) * (i - ii) + vec2_x[ii][j] * vec2_x[ii][j];
                    if (minPOW > temp)
                    {
                        minPOW = temp;
                        min_i = ii;
                    }
                }
                if (min_i != -1)
                {
                    min_j = j + vec2_x_flag[min_i][j] * vec2_x[min_i][j];
                    min_dist_pts[i][j] = vec2{ min_i,min_j };
                    //vec3_out[i][j] = minPOW;
                    vec3_out[i][j] = sqrt(minPOW);
                }
                //vec3_out[i][j] = sqrt(minPOW);
            }
            else
            {
                int r0 = vec3_out[i][j - 1];
                if (r0 == 0)
                {
                    vec3_out[i][j] = 1;
                    min_dist_pts[i][j] = vec2{ i,j - 1 };
                }
                int r1 = r0 + 1;//r上边界
                int r2 = (r0 - 1.0) * sqrt(2) / 2 + 1;//r下边界 是否加一 是
                int cursquare = M;
                int min_i = -1;
                int min_j = -1;
                int dxy = M;
                for (int r = r2; r <= r1; r++)
                {
                    int min_ii = -1;
                    int min_jj = -1;
                    //两竖
                    if (j - r >= 0)
                    {
                        //dxy = std::min(vec2_y[i][j - r], dxy);
                        if (dxy > vec2_y[i][j - r])
                        {
                            dxy = vec2_y[i][j - r];
                            min_ii = i + vec2_y_flag[i][j - r] * vec2_y[i][j - r];
                            min_jj = j - r;
                        }
                    }
                    if (j + r < col)
                    {
                        //dxy = std::min(vec2_y[i][j + r], dxy);
                        if (dxy > vec2_y[i][j + r])
                        {
                            dxy = vec2_y[i][j + r];
                            min_ii = i + vec2_y_flag[i][j + r] * vec2_y[i][j + r];
                            min_jj = j + r;
                        }
                    }
                    //两行
                    if (i - r >= 0)
                    {
                        //dxy = std::min(vec2_x[i - r][j], dxy);
                        if (dxy > vec2_x[i - r][j])
                        {
                            dxy = vec2_x[i - r][j];
                            min_ii = i - r;
                            min_jj = j + vec2_x_flag[i - r][j] * vec2_x[i - r][j];
                        }
                    }
                    if (i + r < row)
                    {
                        //dxy = std::min(vec2_x[i + r][j], dxy);
                        if (dxy > vec2_x[i + r][j])
                        {
                            dxy = vec2_x[i + r][j];
                            min_ii = i + r;
                            min_jj = j + vec2_x_flag[i + r][j] * vec2_x[i + r][j];
                        }
                    }

                    int temp = dxy * dxy + r * r;                  
                    //cursquare = std::min(temp, cursquare);
                    if (cursquare > temp)
                    {
                        cursquare = temp;
                        min_i = min_ii;
                        min_j = min_jj;
                    }
                    if (temp <= (r + 1) * (r + 1))
                    {
                        break;
                    }
                }
                //vec3_out[i][j] = cursquare;
                vec3_out[i][j] = sqrt(cursquare);
                min_dist_pts[i][j] = vec2{ min_i,min_j };
                /*if (cursquare < 0)
                {
                    exit(-60);
                }*/
                /*if (cursquare == M)
                {
                    puts("error");
                }*/
            }
            /*if (vec3_out[i][j][curhei1] < 0)
            {
                exit(-6);
            }*/
        }
    }
}