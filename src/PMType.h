#ifndef PMTYPE_H
#define PMTYPE_H

/**
 * @namespace PMType
 * @brief 定义PMT相关的枚举类型
 * 
 * 包含了光电子响应函数类型和PMT模型类型的枚举定义,
 * 用于在整个框架中统一标识不同的响应类型和模型。
 */
namespace PMType
{
  /**
   * @enum Response
   * @brief 光电子响应函数类型枚举
   * 
   * 定义了可用的单光电子响应函数类型
   */
  enum Response { 
    GAUSS,  // 高斯型响应函数：标准高斯分布模型
    GAMMA   // 伽马型响应函数：使用伽马分布描述光电子响应
  };
  
  /**
   * @enum Model
   * @brief PMT模型类型枚举
   * 
   * 定义了可用的PMT电荷响应模型
   */
  enum Model { 
    SIMPLEGAUSS,  // 简单高斯模型：基础模型，使用标准高斯分布
    TRUNCGAUSS,   // 截断高斯模型：考虑PMT物理限制的高斯模型
    ANATRUNCG,    // 解析截断高斯模型：使用超几何函数的解析方法处理
    EXPTRUNCG     // 显式截断高斯模型：使用预计算多项式系数优化计算效率
  };
    
}
 
#endif
