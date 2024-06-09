import React from 'react';
import { CommentOutlined, CustomerServiceOutlined, CaretUpOutlined, SendOutlined } from '@ant-design/icons';
import { FloatButton } from 'antd';
import 'buffer/'
import { QuillEditor } from 'react-quill';
import ReactQuill from 'react-quill';
import { quillEditorRef } from '../App';
import 'react-quill/dist/quill.snow.css'; // 或 quill.bubble.css
import { cur_cat_filepath } from './menu.js'
import Password from 'antd/es/input/Password.js';
const Submit = () => (
    <>
        <FloatButton.Group
            trigger="click"
            type="primary"
            style={{
                right: 24,
                color: 'white',
                backgroundColor: 'white',
                fill: 'white'
            }}
            icon={<CaretUpOutlined />}
        >
            <FloatButton icon={<SendOutlined />} onClick={submitContent} />
            <FloatButton />
            <FloatButton icon={<CommentOutlined />} />
        </FloatButton.Group>
        {/* <FloatButton icon={<CommentOutlined />} onClick={() => console.log('onClick')} />; */}
        {/* <FloatButton.Group
            trigger="hover"
            type="primary"
            style={{
                right: 94,
            }}
            icon={<CustomerServiceOutlined />}
        >
            <FloatButton />
            <FloatButton icon={<CommentOutlined />} />
        </FloatButton.Group> */}
        {/* <FloatButton icon={<Submit />}></FloatButton> */}
    </>
);
function submitContent() {
    var myHeaders = new Headers();
    myHeaders.append("User-Agent", "Apifox/1.0.0 (https://apifox.com)");
    myHeaders.append("Content-Type", 'application/json;charset=gbk');
    var t = quillEditorRef.current.editor;
    const contents = t.getContents();
    console.log(contents); // 输出 Delta 对象
    // 如果你需要将内容转换为纯文本
    const textContent = t.getText();
    console.log(textContent);
    // 如果你需要 HTML 格式的内容

    const htmlContent = t.root.innerHTML;
    console.log(htmlContent);
    console.log(cur_cat_filepath);
    var raw = JSON.stringify({
        "operation": "registeruser",
        "name": "lili",
        "password": "123456"
    });
    var iconv = require('iconv-lite');
    //gbk
    let gbk_raw = iconv.encode(raw, 'gbk');

    var requestOptions = {
        method: 'POST',
        headers: myHeaders,
        body: gbk_raw,
        redirect: 'follow'
    };

    fetch("http://192.168.38.199:18080/receive_message", requestOptions)
        .then(response => {
            return response.arrayBuffer();
        }).then(data => {
            if (data instanceof ArrayBuffer) {
                // 使用 TextDecoder 解码 ArrayBuffer
                const decoder = new TextDecoder('GBK');
                const gbkString = decoder.decode(data);
                // 如果解码后的数据是 JSON 格式，使用 JSON.parse 转换为对象
                try {
                    const jsonData = JSON.parse(gbkString);
                    console.log(jsonData);
                } catch (e) {
                    console.error('解析 JSON 时出错，可能返回的不是 JSON 格式数据', e);
                }
            } else {
                // 处理正常的 JSON 响应
                console.log(data);
            }
        })
        .catch(error => {
            console.error('请求错误:', error);
        });
}
export default Submit;