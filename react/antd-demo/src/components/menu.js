import {
    Menu,
    Item,
    Separator,
    Submenu,
    useContextMenu
} from "react-contexify";
import {
    DesktopOutlined,
    FileOutlined,
    PieChartOutlined,
    TeamOutlined,
    UserOutlined,
} from '@ant-design/icons';
import { Menu as Antd_Menu, Modal } from 'antd';
import "react-contexify/dist/ReactContexify.css";
import { useState } from "react";
import { OPEN } from '../App.js'
import { My_Form_New_Cat, My_Form_New_File } from './form.js'
function getItem(label, key, icon, id, children = null) {
    return {
        key,
        icon,
        children,
        label,
        id,
    };
}

const MENU_ID = "menu-id";
let cur_item;
let cur_cat_filepath;
const items = [
    getItem('Option 1', '1', <PieChartOutlined />, 'e1', null),
    getItem('Option 2', '2', <DesktopOutlined />, 'e2'),
    getItem('User', 'sub1', <UserOutlined />, 'User', [
        getItem('Tom', '3', null, 'User/Tom'),
        getItem('Bill', '4', null, 'User/Bill'),
        getItem('Alex', '5', null, 'User/Alex'),
    ]),
    getItem('Files', '9', <FileOutlined />, 'Files', []),
];
function Mymenu() {
    const [value, setValue] = useState(items);
    // 🔥 you can use this hook from everywhere. All you need is the menu id
    const { show } = useContextMenu({
        id: MENU_ID
    });
    function displayMenu(e) {
        cur_item = e.currentTarget;
        console.log(cur_item);
        show({
            event: e,
        });
        e.stopPropagation();
    }
    function handleItemClick1({ event, props, triggerEvent, data }) {
        //查询当前项role属性值决定是否可以新建文件
        console.log(cur_item.role);
        //当前item下添加一个新的Item.
        if (cur_item.role == 'none') {
            showModal1();
        } else {
            alert("It is not a group !!!");
        }
    }
    function handleItemClick2({ event, props, triggerEvent, data }) {
        //查询当前项role属性值决定是否可以新建分组
        console.log(cur_item.role);
        //当前item下添加一个新的Item.
        if (cur_item.role == 'none') {
            showModal2();
        } else {
            alert("It is not a group !!!");
        }
    }

    function addItem(items, childItem, parentId) {
        // 遍历items数组
        for (let i = 0; i < items.length; i++) {
            const item = items[i];
            // 检查当前项的id是否与指定的parentId匹配
            if (item.id === parentId) {
                // 如果匹配，添加子项到当前项的children数组中
                if (!item.children) {
                    item.children = []; // 如果当前项没有children属性，初始化为空数组
                }
                item.children.push(childItem);
                return; // 退出函数，因为我们已经找到了父项并添加了子项
            }
            // 如果当前项有子项，递归调用函数在子项中查找
            if (item.children) {
                addItem(item.children, childItem, parentId);
            }
        }
    }
    function createNewFile(filename) {
        var id = cur_item.id;
        var new_id = id + "/" + filename;
        console.log(new_id);
        var addedItme = getItem(filename, null, null, new_id, null);
        addedItme.onContextMenu = displayMenu;
        console.log(addedItme);
        const copiedItems = value.map(item => item);
        addItem(copiedItems, addedItme, id);
        console.log(copiedItems);
        setValue(copiedItems);
    }
    function createNewGroup(groupname) {
        var id = cur_item.id;
        var new_id = id + "/" + groupname;
        console.log(new_id);
        var addedItme = getItem(groupname, null, null, new_id, []);
        addedItme.onContextMenu = displayMenu;
        console.log(addedItme);
        const copiedItems = value.map(item => item);
        addItem(copiedItems, addedItme, id);
        console.log(copiedItems);
        setValue(copiedItems);
    }
    function jump({ key, item }) {
        var id = item.props.id;
        const str_result = id.split('/');
        cur_cat_filepath = str_result;
        var e = document.getElementById("breadcrumb");
        var result="<ol>";
        for(var i=0;i<str_result.length-1;i++){
            result+="<li><span class='ant-breadcrumb-link'>"+str_result[i]+"</span>";
            result+="<li class='ant-breadcrumb-separator' aria-hidden='true'>/</li>";
        }
        result+="<li><span class='ant-breadcrumb-link'>"+str_result[i]+"</span>";
        result+="</ol>"
        e.innerHTML = result;
    }
    // 递归函数来为每个 item 添加新属性
    function addItemPropertyRecursively(item) {
        // 为当前 item 添加新属性
        item.onContextMenu = displayMenu;
        if (item.children == null) {
            item.onClick = jump;
        }
        // 递归地为子 items 添加新属性
        if (item.children) {
            item.children.forEach(addItemPropertyRecursively);
        } return item;
    }
    function initItems() {
        items.map(addItemPropertyRecursively);
    }
    initItems();
    const [open1, setOpen1] = useState(false);
    const [confirmLoading1, setConfirmLoading1] = useState(false);
    const [modalText1, setModalText1] = useState('Content of the modal');
    const [open2, setOpen2] = useState(false);
    const [confirmLoading2, setConfirmLoading2] = useState(false);
    const [modalText2, setModalText2] = useState('Content of the modal');
    const showModal1 = () => {
        setOpen1(true);
    };
    const handleOk1 = () => {
        setModalText1('The modal will be closed after two seconds');
        setConfirmLoading1(true);
        setTimeout(() => {
            setOpen1(false);
            setConfirmLoading1(false);
        }, 200);
    };
    const handleCancel1 = () => {
        console.log('Clicked cancel button');
        setOpen1(false);
    };
    const showModal2 = () => {
        setOpen2(true);
    };
    const handleOk2 = () => {
        setModalText2('The modal will be closed after two seconds');
        setConfirmLoading2(true);
        setTimeout(() => {
            setOpen2(false);
            setConfirmLoading2(false);
        }, 200);
    };
    const handleCancel2 = () => {
        console.log('Clicked cancel button');
        setOpen2(false);
    };
    return (
        <>
            <div>
                <Antd_Menu theme="dark" defaultSelectedKeys={['1']} mode="inline" items={value} />
                <Menu id={MENU_ID}>
                    <Item onClick={handleItemClick1}>
                        新建文件
                    </Item>
                    <Item onClick={handleItemClick2}>
                        新建分组
                    </Item>
                    <Separator />
                    <Item disabled>Disabled</Item>
                    <Separator />
                    <Submenu label="子菜单">
                        <Item onClick={handleItemClick1}>
                            Sub Item 1
                        </Item>
                        <Item onClick={handleItemClick2}>Sub Item 2</Item>
                    </Submenu>
                </Menu>
                <Modal
                    open={open1}
                    onOk={handleOk1}
                    confirmLoading={confirmLoading1}
                    onCancel={handleCancel1}
                    footer={null}
                >
                    <My_Form_New_File finish={handleOk1} newfile={createNewFile} />
                </Modal>
                <Modal
                    open={open2}
                    onOk={handleOk2}
                    confirmLoading={confirmLoading2}
                    onCancel={handleCancel2}
                    footer={null}
                >
                    <My_Form_New_Cat finish={handleOk2} newGroup={createNewGroup} />
                </Modal>
            </div>
        </>
    );
}



export { Mymenu,cur_cat_filepath };