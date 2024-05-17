# BlueprintVersionControl
 BlueprintVersionControl

## 介绍
这是一个用于蓝图版本控制的插件。它会遍历所有的蓝图。然后遍历蓝图中的节点。最后把节点信息保存到.json中。进而实现蓝图的版本控制。

## 未来优化
- 性能优化1：把逻辑放在其它的线程。  
- 性能优化2：只更新dirty的蓝图资产。  
- 功能优化：包含更多更详细的节点信息。  
- 触发优化：与保存资产的委托绑定。  

## 优势
- 解决蓝图内容无法清晰地进行版本控制的问题。

# BlueprintVersionControl
 BlueprintVersionControl

## Introduction
 BlueprintVersionControl is a plug-in for blueprint version control. It goes through all blueprints, checks all the nodes in the blueprints, and finally saves the node information to a .json file to realize the version control of the blueprint.

## Future Optimizations
- Performance optimization 1: Move the logic to other threads.
- Performance optimization 2: Only update dirty blueprint resources.
- Functional optimization: Include more detailed node information.
- Triggering optimization: Bind to the delegate saving the resources.

## Advantages
- Solves the problem wherein the content of the blueprint cannot be clearly version-controlled.