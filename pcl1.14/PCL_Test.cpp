#include <iostream>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

int main() {
    std::cout << "PCL 版本测试" << std::endl;
    std::cout << "PCL 版本: " << PCL_VERSION << std::endl;
    
    // 创建一个简单的点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);
    
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = i * 1.0;
        cloud->points[i].y = i * 2.0;
        cloud->points[i].z = i * 3.0;
    }
    
    std::cout << "创建了点云，包含 " << cloud->size() << " 个点" << std::endl;
    
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        std::cout << "点 " << i << ": (" 
                  << cloud->points[i].x << ", " 
                  << cloud->points[i].y << ", " 
                  << cloud->points[i].z << ")" << std::endl;
    }
    // 等待用户按回车键
    std::cout << "\n按回车键退出...";
    std::cin.get();  // 等待用户输入
    
    return 0;
}