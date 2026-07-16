# 上位机与接口 (C# / WPF)

## 目录结构
```
04_UI_Integration/
├── DLL_Imports/                 # C# P/Invoke 接口封装
│   ├── NativeMethods.cs         # DLL 导入定义
│   └── StereoApi.cs             # 封装后的托管 API
├── Visualization_Components/    # 深度图、点云渲染控件
│   ├── DepthView.xaml           # 深度图显示控件
│   ├── PointCloudView.xaml      # 点云 3D 渲染控件
│   └── Controls/
```

## 接口规范
- C++ DLL 导出纯 C 接口，便于 C# P/Invoke
- 数据结构通过 `IntPtr` + `Marshal.StructureToPtr` 传递
- 图像数据通过共享内存 / 内存映射文件传递

> 代码由开发者上传
