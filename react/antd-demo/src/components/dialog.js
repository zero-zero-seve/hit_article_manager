import React, { useState } from 'react';
import { Button, Modal } from 'antd';
import MyForm from './form.js'

const Dialog = ({ isOpen }) => {
    const [open, setOpen] = useState(isOpen);
    const [confirmLoading, setConfirmLoading] = useState(false);
    const [modalText, setModalText] = useState('Content of the modal');
    const showModal = () => {
        setOpen(true);
    };
    const handleOk = () => {
        setModalText('The modal will be closed after two seconds');
        setConfirmLoading(true);
        // setTimeout(() => {
        //     setOpen(false);
        //     setConfirmLoading(false);
        // }, 2000000000000000000000000000);
    };
    const handleCancel = () => {
        console.log('Clicked cancel button');
        setOpen(false);
    };
    return (
        <>
            {/* <li type="primary" onClick={showModal}>
                Open Modal
            </li> */}
            <Modal
                title="Title"
                open={open}
                onOk={handleOk}
                confirmLoading={confirmLoading}
                onCancel={handleCancel}
            >
                {/* <MyForm /> */}
            </Modal>
        </>
    );
};




export { Dialog };

