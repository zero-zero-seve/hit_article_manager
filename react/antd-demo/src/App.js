// import React, { useState } from 'react';
// import {
//   MenuFoldOutlined,
//   MenuUnfoldOutlined,
//   UploadOutlined,
//   UserOutlined,
//   VideoCameraOutlined,
// } from '@ant-design/icons';
// import { Button, Layout, Menu, theme } from 'antd';
// const { Header, Sider, Content } = Layout;
// const App = () => {
//   const [collapsed, setCollapsed] = useState(false);
//   const {
//     token: { colorBgContainer, borderRadiusLG },
//   } = theme.useToken();
//   return (
//     <Layout>
//       <Sider trigger={null} collapsible collapsed={collapsed}>
//         <div className="demo-logo-vertical" />
//         <Menu
//           theme="dark"
//           mode="inline"
//           defaultSelectedKeys={['1']}
//           items={[
//             {
//               key: '1',
//               icon: <UserOutlined />,
//               label: 'nav 1',
//             },
//             {
//               key: '2',
//               icon: <VideoCameraOutlined />,
//               label: 'nav 2',
//             },
//             {
//               key: '3',
//               icon: <UploadOutlined />,
//               label: 'nav 3',
//             },
//             {

//             }
//           ]}
//         />
//       </Sider>
//       <Layout style={{ height: '100%' }}>
//         <Header
//           style={{
//             padding: 0,
//             background: colorBgContainer,
//           }}
//         >
//           <Button
//             type="text"
//             icon={collapsed ? <MenuUnfoldOutlined /> : <MenuFoldOutlined />}
//             onClick={() => setCollapsed(!collapsed)}
//             style={{
//               fontSize: '16px',
//               width: 64,
//               height: 64,
//             }}
//           />
//         </Header>
//         <Content
//           style={{
//             margin: '24px 16px',
//             padding: 24,
//             minHeight: '600px',
//             height: '100%',
//             background: colorBgContainer,
//             borderRadius: borderRadiusLG,
//           }}
//         >
//           Content
//         </Content>
//       </Layout>
//     </Layout>
//   );
// };
// export default App;



import React, { useState, useRef, useEffect } from 'react';
import {
  DesktopOutlined,
  FileOutlined,
  PieChartOutlined,
  TeamOutlined,
  UserOutlined,
} from '@ant-design/icons';
import { Breadcrumb, Layout, Menu, theme, Input } from 'antd';
import './components/menu.js'
import { QuillEditor } from 'react-quill';
import ReactQuill from 'react-quill';
import 'react-quill/dist/quill.snow.css'; // 或 quill.bubble.css
import './css/text_editor.css'
import FLOATBUTTON from './components/float_button.js'
import { Mymenu, TestMenu } from './components/menu.js';
import { Dialog } from "./components/dialog.js"
const { Header, Content, Footer, Sider } = Layout;

let quillEditorRef;
function TextEditor() {
  // 用于保存编辑器内容的状态
  const [value, setValue] = React.useState('');

  // 处理文本变化的函数
  const handleChange = (content) => {
    setValue(content);
  };
  quillEditorRef = useRef(null);
  // 使用 useEffect 钩子来执行副作用操作
  const modules = {
    toolbar: [
      ['bold', 'italic', 'underline', 'strike'],        // 基础样式
      ['blockquote', 'code-block'],              // 引用和代码块
      [{ 'header': 1 }, { 'header': 2 }],               // 标题
      [{ 'list': 'ordered' }, { 'list': 'bullet' }],    // 列表
      ['link', 'image'],                             // 链接和图片
      ['clean']                                     // 清除格式
    ],
  };
  return (
    <div>
      <ReactQuill ref={quillEditorRef} modules={modules} minHeight='600' value={value} onChange={handleChange} style={{ height: '500px' }} id="editor" placeholder='your edit area' />;
    </div>
  );
}


const App = () => {
  const [collapsed, setCollapsed] = useState(false);
  const {
    token: { colorBgContainer, borderRadiusLG },
  } = theme.useToken();

  return (
    <Layout
      style={{
        minHeight: '100vh',
      }}
    >
      <Sider collapsible collapsed={collapsed} onCollapse={(value) => setCollapsed(value)}>
        <div className="demo-logo-vertical" />
        <Mymenu />
      </Sider>
      <Layout>
        <Header
          style={{
            padding: 0,
            background: colorBgContainer,
          }}
        />
        <Content
          style={{
            margin: '0 16px',
            // minHeight: '650 px'
          }}
        >
          <Breadcrumb 
          id="breadcrumb"
            style={{
              margin: '16px 0',
            }}
          >
            <Breadcrumb.Item>User</Breadcrumb.Item>
            <Breadcrumb.Item>Bill</Breadcrumb.Item>
          </Breadcrumb>
          <div
            style={{
              padding: 24,
              minHeight: 600,
              background: colorBgContainer,
              borderRadius: borderRadiusLG,
            }}
          >
            <TextEditor />
            <FLOATBUTTON />
          </div>
        </Content>
      </Layout>
    </Layout>
  );
};
export { App, quillEditorRef };


