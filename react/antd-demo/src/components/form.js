import React from 'react';
import { Button, Form, Input } from 'antd';
import './form.css'
const MyFormItemContext = React.createContext([]);

function toArr(str) {
    return Array.isArray(str) ? str : [str];
}
const MyFormItemGroup = ({ prefix, children }) => {
    const prefixPath = React.useContext(MyFormItemContext);
    const concatPath = React.useMemo(() => [...prefixPath, ...toArr(prefix)], [prefixPath, prefix]);
    return <MyFormItemContext.Provider value={concatPath}>{children}</MyFormItemContext.Provider>;
};
const MyFormItem = ({ name, ...props }) => {
    const prefixPath = React.useContext(MyFormItemContext);
    const concatName = name !== undefined ? [...prefixPath, ...toArr(name)] : undefined;
    return <Form.Item name={concatName} {...props} />;
};
const My_Form_New_File = ({ finish, newfile }) => {
    const [form] = Form.useForm(); // 使用 useForm 钩子创建表单实例
    const onFinish = (values) => {
        console.log(values); // 打印表单数据
        var filename = values["newFile"];
        finish();
        newfile(filename);
    };
    // 处理按钮点击的函数，提交表单
    const handleButtonClick = () => {
        form.validateFields().then(values => {
            onFinish(values); // 调用 onFinish 处理表单数据
        }).catch(info => {
            console.log('Failed:', info);
        });
    };
    return (
        <Form form={form} name="form_item_path" layout="vertical" onFinish={onFinish} id="getnameform">
            <MyFormItem name="newFile" label="Filename">
                <Input />
            </MyFormItem>
            <div id="newFile">
                <div id="newFile1"></div>
                <Button type="primary" id="newFile2" onClick={handleButtonClick}>
                    NEW
                </Button>
            </div>
        </Form>
    );
};


const My_Form_New_Cat = ({ finish, newGroup }) => {
    const [form] = Form.useForm(); // 使用 useForm 钩子创建表单实例
    const onFinish = (values) => {
        console.log(values); // 打印表单数据
        var groupname = values["newFileGroup"];
        finish();
        newGroup(groupname);

    };
    // 处理按钮点击的函数，提交表单
    const handleButtonClick = () => {
        form.validateFields().then(values => {
            onFinish(values); // 调用 onFinish 处理表单数据
        }).catch(info => {
            console.log('Failed:', info);
        });
    };
    return (
        <Form form={form} name="form_item_path" layout="vertical" onFinish={onFinish} id="getnameform">
            <MyFormItem name="newFileGroup" label="Groupname">
                <Input />
            </MyFormItem>
            <div id="newFile">
                <div id="newFile1"></div>
                <Button type="primary" id="newFile2" onClick={handleButtonClick}>
                    NEW
                </Button>
            </div>
        </Form>
    );
};
export { My_Form_New_Cat, My_Form_New_File };