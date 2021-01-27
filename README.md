# MYVIM
数据结构课程设计 简易文本编辑器
### 主要特点
- 使用链表存储数据
- 支持文件读取和保存
- 使用链栈实现了撤回和重做操作
- UI自适应控制台大小
- 不支持中文输入
### 功能模式（默认）
- i 进入插入模式
- u 撤回此前操作
- r 重做已撤回的操作
- s 保存文件
- o 打开文件
- q 退出程序
### INSERTMODE插入模式

- Esc 返回功能模式
- 插入任意字符
- Backspace 删除字符
- Enter 换行
- 方向键 移动光标
- Ctrl+V 粘贴
### TODO
- [x] 基本框架
- [x] 链栈
- [x] 撤回功能
- [x] 重做bug
- [x] 保存读取功能
- [x] UI显示
- [x] 帮助界面显示
- [x] Tab支持
- [x] 操作优化（对话类）
