# **2D Roguelike на C++ со своим движком (SFML)** 

Учебный проект в жанре Roguelike с процедурной генерацией лабиринтов, боевой системой.
Игра построена на собственном 2D-движке поверх C++17 и SFML 2.5.1.

 ## Геймплей

	• Процедурная генерация уровней (LabyrinthBuilder).

	• Враги с ИИ (AIMovementComponent), фабрики врагов и состояния врага.

	• Характеристики персонажа (StatsComponent).

	• Боевая система (компоненты атак и ориентации спрайта).

## Управление

	• WASD / стрелки — перемещение

	• Left Shift - блок

	• ЛКМ — атака

## Структура проекта

	• Engine — собственный 2D-движок

	• Roguelike — игровая логика:

	• генерация лабиринтов и создание уровней

	• объекты (игрок, враги, стены, пол, музыка)

	• бой, ориентация спрайтов

## Технологии

	• C++20

	• SFML 2.5.1

	• Visual Studio 2022

## Движок (модуль Engine)

	• Компонентно-ориентированная архитектура:

	• Ввод: InputComponent

	• Игровые объекты: GameObject, Component

	• Рендер: RenderSystem (спрайты, камера)

	• Коллизии и физика: Collision, PhysicsSystem

	• Ресурсы: ResourceSystem (текстуры, звуки и шрифты)

	• Звук: SoundComponent

	• Логирование: Logger, ConsoleSink, LogSink, FileSink, LoggerRegister

	• Трансформации: TransformComponent - позиция/поворот/масштаб

	• Математика: Vector - векторы, Matrix2D - матрицы

	• Камера и игровой мир

## Запуск проекта

	• Необходимо скачать готовый билд-архив (Roguelike_x64-Release.zip) по URL:
	https://github.com/log-In-up/Roguelike/releases/tag/Diploma-1

	• Запустить исполняемый файл по умолчанию: Roguelike.exe

## Дополнительные ассеты используемые в проекте

	• - Tiny RPG Character Asset Pack v1.03
	https://zerie.itch.io/tiny-rpg-character-asset-pack