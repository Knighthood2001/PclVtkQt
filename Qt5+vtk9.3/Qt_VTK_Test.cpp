#include <QApplication>
#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>  // 添加这个头文件
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>  // 添加这个头文件
#include <vtkRenderWindowInteractor.h>  // 添加这个头文件
#include <iostream>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        std::cout << "创建主窗口..." << std::endl;
        
        try {
            // 创建VTK窗口部件
            vtkWidget = new QVTKOpenGLNativeWidget(this);
            if (!vtkWidget) {
                std::cerr << "无法创建QVTKOpenGLNativeWidget" << std::endl;
                return;
            }
            setCentralWidget(vtkWidget);
            
            std::cout << "创建vtkGenericOpenGLRenderWindow..." << std::endl;
            
            // 关键：创建vtkGenericOpenGLRenderWindow
            vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = 
                vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
            
            if (!renderWindow) {
                std::cerr << "无法创建vtkGenericOpenGLRenderWindow" << std::endl;
                return;
            }
            
            // 设置渲染窗口
            vtkWidget->setRenderWindow(renderWindow);
            
            std::cout << "创建渲染器..." << std::endl;
            
            // 创建渲染器
            vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
            renderWindow->AddRenderer(renderer);
            
            std::cout << "创建球体..." << std::endl;
            
            // 创建球体
            vtkSmartPointer<vtkSphereSource> sphereSource = 
                vtkSmartPointer<vtkSphereSource>::New();
            sphereSource->SetRadius(2.0);
            sphereSource->SetThetaResolution(30);
            sphereSource->SetPhiResolution(30);
            
            vtkSmartPointer<vtkPolyDataMapper> mapper = 
                vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputConnection(sphereSource->GetOutputPort());
            
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetMapper(mapper);
            actor->GetProperty()->SetColor(0.0, 0.8, 0.3);
            actor->GetProperty()->SetOpacity(0.8);
            
            renderer->AddActor(actor);
            renderer->SetBackground(0.1, 0.1, 0.2);
            
            // 设置相机位置
            renderer->GetActiveCamera()->SetPosition(0, 0, 10);
            renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
            renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
            renderer->ResetCamera();
            
            // 设置交互器样式
            vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
                vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
            renderWindow->GetInteractor()->SetInteractorStyle(style);
            
            // 渲染
            renderWindow->Render();
            
            std::cout << "VTK渲染完成" << std::endl;
            
            setWindowTitle("VTK 9.3 + Qt 5.15.2 Test");
            resize(800, 600);
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    ~MainWindow() {
        if (vtkWidget && vtkWidget->renderWindow()) {
            vtkWidget->renderWindow()->Finalize();
        }
    }
    
protected:
    void closeEvent(QCloseEvent* event) override {
        if (vtkWidget && vtkWidget->renderWindow()) {
            vtkWidget->renderWindow()->Finalize();
        }
        QMainWindow::closeEvent(event);
    }
    
private:
    QVTKOpenGLNativeWidget* vtkWidget;
};

int main(int argc, char** argv) {
    std::cout << "Program starting..." << std::endl;
    // 设置Qt插件路径（解决插件找不到的问题）
    //QApplication::addLibraryPath("I:/cpppackage/Qt/5.15.2/msvc2019_64/plugins");
    
    QApplication app(argc, argv);
    
    std::cout << "Creating main window..." << std::endl;
    MainWindow mainWindow;
    
    std::cout << "Showing window..." << std::endl;
    mainWindow.show();
    
    std::cout << "Entering event loop..." << std::endl;
    return app.exec();
}