#pragma once

#include <stack>

class NodeScene;

class NodeSceneHistory
{
public:
    NodeSceneHistory(NodeScene* scene);
    ~NodeSceneHistory() {}

    void undo();
    void redo();

    void restoreHistory();
    void restoreHistoryStamp(void* historyStamp); 

private:
    NodeScene* m_Scene = nullptr;
    uint32_t m_HistoryLimit = 8;
    int32_t m_CurrentHistoryStep = -1;
    std::stack<void*> m_HistoryStack;
};

